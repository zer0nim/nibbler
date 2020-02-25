#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <algorithm>

#include "ANibblerGui.hpp"
#include "GameManager.hpp"

// -- Constructors -------------------------------------------------------------

GameManager::GameManager(GameInfo &gameInfo)
: _gameInfo(gameInfo) {
	_gameInfo.direction = Direction::MOVE_UP;
	_eating = 0;
	_lanMode = LAN_MODE::SOLO;
}

GameManager::~GameManager() {
	delete lHost;
	delete lClient;
}

GameManager::GameManager(GameManager const &src):
 _gameInfo(src._gameInfo) {
	*this = src;
}

// -- Operators ----------------------------------------------------------------

GameManager &GameManager::operator=(GameManager const &rhs) {
	if ( this != &rhs ) {
		_gameInfo.direction = rhs._gameInfo.direction;
		_eating = rhs._eating;
		_lanMode = rhs._lanMode;
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

	result += "Gameboard [" + std::to_string(_gameInfo.gameboard.x) + ", "
			+ std::to_string(_gameInfo.gameboard.y) + "]\n"
			"snake length: " + std::to_string(_gameInfo.snake.size()) + "\n"
			"game [";
	switch (_gameInfo.play) {
	case State::S_PLAY:
		result += "PLAY";
		break;
	case State::S_PAUSE:
		result += "PAUSE";
		break;
	case State::S_GAMEOVER:
		result += "GAME OVER";
		break;
	default:
		break;
	}
	result += "]\n";

	result += getBoard();

	for (glm::ivec2 const &i : _gameInfo.snake) {
		result += ">>" + glm::to_string(i);
	}

	return result;
}

std::string	GameManager::getBoard() const {
	std::string result;

	for (int j = 0; j < _gameInfo.gameboard.y; j++) {
		for (int i = 0; i < _gameInfo.gameboard.x; i++) {
			if (!isEmpty(glm::ivec2(i, j))) {
				if (_gameInfo.food == glm::ivec2(i, j))
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

glm::ivec2	GameManager::getHead() const {
	return _gameInfo.snake.front();
}

// -- Methods ------------------------------------------------------------------

bool	GameManager::init(int8_t guiId, LAN_MODE::Enum lanMode) {
	// if we play solo or we are host then init game
	if (lanMode == LAN_MODE::SOLO || lanMode == LAN_MODE::HOST) {
		// init snake
		_gameInfo.snake.push_back({1, 1});
		_gameInfo.snake.push_back({1, 2});
		_gameInfo.snake.push_back({1, 3});
		_gameInfo.snake.push_back({1, 4});
		_gameInfo.snake.push_back({1, 5});
		_gameInfo.snake.push_back({1, 6});
		_gameInfo.snake.push_back({1, 7});
		_gameInfo.snake.push_back({1, 8});

		// place initial food
		srand(time(NULL));  // set random seed
		_generateFood();
	}
	else {
		// TODO(zer0nim): need to tell host to init player
	}

	// init gui if id is valid
	if (guiId != EMPTY_GUI_ID) {
		_lanMode = lanMode;
		_dynGuiManager.loadGui(guiId);
		return _dynGuiManager.nibblerGui->init(_gameInfo);
	}
	return true;
}

void	GameManager::restart() {
	_gameInfo.direction = Direction::MOVE_UP;
	_eating = 0;
	_gameInfo.food = VOID_POS;
	_gameInfo.snake.clear();
	init(EMPTY_GUI_ID, _lanMode);
	_gameInfo.play = State::S_PAUSE;
}

void	GameManager::run() {
	float						loopTime = 1000 / FPS;
	std::chrono::milliseconds	time_start;
	ANibblerGui					*nibblerGui = nullptr;
	#if DEBUG_FPS_LOW == true
		bool firstLoop = true;
	#endif


	nibblerGui = _dynGuiManager.nibblerGui;

	while (nibblerGui->input.quit == false) {
		time_start = _getMs();
		nibblerGui->updateInput();

		// toggle play/pause
		if (nibblerGui->input.togglePause && _gameInfo.play != State::S_GAMEOVER) {
			if (_gameInfo.play == State::S_PAUSE)
				_gameInfo.play = State::S_PLAY;
			else if (_gameInfo.play == State::S_PLAY)
				_gameInfo.play = State::S_PAUSE;
		}
		// restart if the player is dead
		else if (nibblerGui->input.togglePause) {
			restart();
		}

		if (_gameInfo.play == State::S_PAUSE && nibblerGui->input.direction != Direction::NO_MOVE)
			_gameInfo.play = State::S_PLAY;

		// on play mode
		if (_gameInfo.play == State::S_PLAY) {
			_move(nibblerGui->input.direction);
			_checkContact();
		}

		// verify id viability
		if (nibblerGui->input.loadGuiID < NB_GUI && \
		nibblerGui->input.loadGuiID != _dynGuiManager.getCurrentGuiID()) {
			if (_gameInfo.play != State::S_GAMEOVER) {
				_gameInfo.play = State::S_PAUSE;
			}
			// change Gui
			_dynGuiManager.loadGui(nibblerGui->input.loadGuiID);
			nibblerGui = _dynGuiManager.nibblerGui;
			nibblerGui->init(_gameInfo);

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

bool	GameManager::_move(Direction::Enum dir) {
	glm::ivec2 head = getHead();

	dir = _acceptedDirection(dir);
	_gameInfo.direction = dir;

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
	// std::cout << "[head :" << glm::to_string(head);
	head.x = (head.x + _gameInfo.gameboard.x) % _gameInfo.gameboard.x;
	head.y = (head.y + _gameInfo.gameboard.y) % _gameInfo.gameboard.y;
	// std::cout << ", normalized: " << glm::to_string(head) << "]" << std::endl;
	_gameInfo.snake.push_front(head);
	if (_eating <= 0) {
		_gameInfo.snake.pop_back();
		if (_eating < 0)
			_eating = 0;
	} else {
		_eating -= 1;
	}
	return true;
}

Direction::Enum	GameManager::_acceptedDirection(Direction::Enum dir) {
	switch (dir) {
	case Direction::MOVE_UP:
		if (_gameInfo.direction == Direction::MOVE_DOWN)
			return _gameInfo.direction;
		return dir;
	case Direction::MOVE_RIGHT:
		if (_gameInfo.direction == Direction::MOVE_LEFT)
			return _gameInfo.direction;
		return dir;
	case Direction::MOVE_DOWN:
		if (_gameInfo.direction == Direction::MOVE_UP)
			return _gameInfo.direction;
		return dir;
	case Direction::MOVE_LEFT:
		if (_gameInfo.direction == Direction::MOVE_RIGHT)
			return _gameInfo.direction;
		return dir;
	default:
		return _gameInfo.direction;
		break;
	}
}

bool	GameManager::isEmpty(glm::ivec2 pos, bool head) const {
	if (pos == _gameInfo.food)
		return false;
	if (std::find(head ? ++_gameInfo.snake.begin() : _gameInfo.snake.begin(), _gameInfo.snake.end(), pos)
		!= _gameInfo.snake.end())
		return false;
	return true;
}

bool GameManager::_checkContact() {
	glm::ivec2 head = getHead();

	if (isEmpty(head, true))
		return true;

	if (head == _gameInfo.food) {
		_eating += 9;
		_generateFood();
		return true;
	} else {
		_gameInfo.play = State::S_GAMEOVER;
		return false;
	}
}

void	GameManager::_generateFood() {
	glm::ivec2 food;

	do {
		food.x = rand() % _gameInfo.gameboard.x;
		food.y = rand() % _gameInfo.gameboard.y;
	} while (!isEmpty(food));
	_gameInfo.food = food;
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
