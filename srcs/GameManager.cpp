#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include "GameManager.hpp"

// -- Constructors -------------------------------------------------------------

GameManager::GameManager() {
	_moveSpeed = 3.0f;
	_play = State::S_PAUSE;
	_gameboard = glm::ivec2(25, 25);
	_body = new std::deque<glm::ivec2>();
	_direction = Direction::MOVE_RIGHT;
	_food = {-1, -1};
	_eating = 0;
}

GameManager::GameManager(int height, int width, float moveSpeed)
: _moveSpeed(moveSpeed) {
	_body = new std::deque<glm::ivec2>();
	_gameboard = glm::ivec2(height, width);
	_play = State::S_PAUSE;
	_direction = Direction::MOVE_RIGHT;
	_food = {-1, -1};
	_eating = 0;
}

GameManager::~GameManager() {
	delete _body;
}

GameManager::GameManager(GameManager const &src) {
	*this = src;
}

// -- Operators ----------------------------------------------------------------

GameManager &GameManager::operator=(GameManager const &rhs) {
	if ( this != &rhs ) {
		_body = new std::deque<glm::ivec2>(*rhs._body);
		_moveSpeed = rhs._moveSpeed;
		_play = rhs._play;
		_gameboard = rhs._gameboard;
	}
	return *this;
}

std::ostream &	operator<<(std::ostream & os, const GameManager& my_class) {
	os << my_class.toString() << std::endl;
	return (os);
}

// -- Accessors ----------------------------------------------------------------

std::string	GameManager::toString() const {
	std::string result = "";

	result += "Gameboard [" + std::to_string(_gameboard.x) + ", "
			+ std::to_string(_gameboard.y) + "]\n"
			"snake length: " + std::to_string(_body->size()) + "\n";

	result += getBoard();

	for (glm::ivec2 const &i : *_body) {
		result += ">>" + glm::to_string(i);
	}

	return result;
}

std::string	GameManager::getBoard() const {
	std::string result;

	for (int j = 0; j < _gameboard.y; j++) {
		for (int i = 0; i < _gameboard.x; i++) {
			if (!_isEmpty(glm::ivec2(i, j))) {
				if (_food == glm::ivec2(i, j))
					result += COLOR_GREEN "o" COLOR_EOC;
				else if (getHead() == glm::ivec2(i, j))
					result += COLOR_RED "x" COLOR_EOC;
				else
					result += "x";
			} else
				result += "_";
		}
		result += "\n";
	}
	return result;
}

std::deque<glm::ivec2>	*GameManager::getBody() const {
	return _body;
}

glm::ivec2	GameManager::getHead() const {
	return _body->front();
}

// -- Methods ------------------------------------------------------------------

bool	GameManager::init() {
	uint8_t			guiId = 0;

	_body->push_back({1, 1});
	_body->push_back({1, 2});
	_body->push_back({1, 3});

	std::cout << "srand" << std::endl;
	srand(time(NULL));

	_generateFood();

	dynGuiManager.loadGui(guiId);
	return dynGuiManager.nibblerGui->init();
}

void	GameManager::run() {
	float						loopTime = 1000 / FPS;
	std::chrono::milliseconds	time_start;
	ANibblerGui					*nibblerGui = nullptr;
	#if DEBUG_FPS_LOW == true
		bool firstLoop = true;
	#endif


	nibblerGui = dynGuiManager.nibblerGui;

	while (nibblerGui->input.quit == false) {
		time_start = _getMs();
		nibblerGui->updateInput();

		if (_play == State::S_PAUSE && nibblerGui->input.direction != Direction::NO_MOVE)
			_play = State::S_PLAY;

		logDebug("Game : " << *this);
		logDebug("moving direction " << nibblerGui->input.direction);

		if (_play == State::S_PLAY) {
			_move(nibblerGui->input.direction);
			_checkContact();
		}

		// verify id viability
		if (nibblerGui->input.loadGuiID < NB_GUI && \
		nibblerGui->input.loadGuiID != dynGuiManager.getCurrentGuiID()) {
			// change Gui
			dynGuiManager.loadGui(nibblerGui->input.loadGuiID);
			nibblerGui = dynGuiManager.nibblerGui;
			nibblerGui->init();

			nibblerGui->input.loadGuiID = NO_GUI_LOADED;
		}

		nibblerGui->draw();

		// fps
		std::chrono::milliseconds time_loop = _getMs() - time_start;
		if (time_loop.count() > loopTime) {
			#if DEBUG_FPS_LOW == true
				if (!firstLoop)
					logDebug("update loop slow -> " << time_loop.count() << "ms / " << loopTime << "ms (" << FPS << "fps)");
			#endif
		}
		else {
			usleep((loopTime - time_loop.count()) * 1000);
		}
		#if DEBUG_FPS_LOW == true
			firstLoop = false;
		#endif
	}
}

bool	GameManager::_move(Direction::eDirection dir) {
	glm::ivec2 head = getHead();

	dir = _acceptedDirection(dir);
	_direction = dir;

	switch (dir) {
		case Direction::MOVE_UP:
			head += V_UP;
			break;
		case Direction::MOVE_RIGHT:
			head += V_RIGHT;
			break;
		case Direction::MOVE_DOWN:
			head += V_DOWN;
			break;
		case Direction::MOVE_LEFT:
			head += V_LEFT;
			break;
		default:
			return false;
	}
	std::cout << "[head :" << glm::to_string(head);
	head.x = (head.x + _gameboard.x) % _gameboard.x;
	head.y = (head.y + _gameboard.y) % _gameboard.y;
	std::cout << ", normalized: " << glm::to_string(head) << "]" << std::endl;
	_body->push_front(head);
	if (_eating <= 0) {
		_body->pop_back();
		if (_eating < 0)
			_eating = 0;
	} else {
		_eating -= 1;
	}
	return true;
}

Direction::eDirection	GameManager::_acceptedDirection(Direction::eDirection dir) {
	switch (dir) {
	case Direction::MOVE_UP:
		if (_direction == Direction::MOVE_DOWN)
			return _direction;
		return dir;
	case Direction::MOVE_RIGHT:
		if (_direction == Direction::MOVE_LEFT)
			return _direction;
		return dir;
	case Direction::MOVE_DOWN:
		if (_direction == Direction::MOVE_UP)
			return _direction;
		return dir;
	case Direction::MOVE_LEFT:
		if (_direction == Direction::MOVE_RIGHT)
			return _direction;
		return dir;
	default:
		return _direction;
		break;
	}
}

bool	GameManager::_isEmpty(glm::ivec2 pos) const {
	if (pos == _food)
		return false;
	if (std::find(_body->begin(), _body->end(), pos) != _body->end())
		return false;
	return true;
}

bool GameManager::_checkContact() {
	glm::ivec2 head = getHead();

	if (_isEmpty(head))
		return true;

	if (head == _food) {
		_eating += 1;
		_generateFood();
		return true;
	} else {
		_play = State::S_GAMEOVER;
		return false;
	}
}

void	GameManager::_generateFood() {
	glm::ivec2 food;

	do {
		food.x = rand() % _gameboard.x;
		food.y = rand() % _gameboard.y;
	} while (!_isEmpty(food));
	_food = food;
}

std::chrono::milliseconds GameManager::_getMs() {
	return std::chrono::duration_cast<std::chrono::milliseconds>(
		std::chrono::system_clock::now().time_since_epoch());
}

// -- Exceptions errors --------------------------------------------------------

GameManager::GameManagerException::GameManagerException()
: std::runtime_error("GameManager Exception") {}

GameManager::GameManagerException::GameManagerException(const char* what_arg)
: std::runtime_error(std::string(std::string("GameManagerError: ") + what_arg).c_str()) {}
