#include "NibblerSFML.hpp"
#include "Logging.hpp"

NibblerSFML::NibblerSFML() :
  ANibblerGui(),
  _win() {
	// init logging
	#if DEBUG
		logging.setLoglevel(LOGDEBUG);
		logging.setPrintFileLine(LOGWARN, true);
		logging.setPrintFileLine(LOGERROR, true);
		logging.setPrintFileLine(LOGFATAL, true);
	#else
		logging.setLoglevel(LOGINFO);
	#endif

	_h_block = 10;
	_w_block = 10;
	_h_margin = 5;
	_w_margin = 5;
}

NibblerSFML::~NibblerSFML() {
	logInfo("exit SFML");
	_win.close();
}

NibblerSFML::NibblerSFML(NibblerSFML const &src) {
	*this = src;
}

NibblerSFML &NibblerSFML::operator=(NibblerSFML const &rhs) {
	if (this != &rhs) {
		logErr("unable to copy NibblerSFML");
	}
	return *this;
}

bool NibblerSFML::init(GameInfo &gameInfo) {
	logInfo("loading SFML");

	_win.create(sf::VideoMode(gameInfo.windowSize.x, gameInfo.windowSize.y), TITLE);

	this->gameInfo = &gameInfo;

	return true;
}

void NibblerSFML::updateInput() {
	input.direction = Direction::NO_MOVE;
	while (_win.pollEvent(_event)) {
		switch (_event.type) {
			// window closed
			case sf::Event::Closed:
				input.quit = true;
				break;

			// key pressed
			case sf::Event::KeyPressed:
				if (_event.key.code == sf::Keyboard::Escape)
					input.quit = true;

				else if (_event.key.code == sf::Keyboard::Up)
					input.direction = Direction::MOVE_UP;
				else if (_event.key.code == sf::Keyboard::Right)
					input.direction = Direction::MOVE_RIGHT;
				else if (_event.key.code == sf::Keyboard::Down)
					input.direction = Direction::MOVE_DOWN;
				else if (_event.key.code == sf::Keyboard::Left)
					input.direction = Direction::MOVE_LEFT;


				else if (_event.key.code == sf::Keyboard::Num1)
					input.loadGuiID = 0;
				else if (_event.key.code == sf::Keyboard::Num2)
					input.loadGuiID = 1;
				else if (_event.key.code == sf::Keyboard::Num3)
					input.loadGuiID = 2;
				break;

			default:
				break;
		}
	}
}

bool NibblerSFML::draw() {
	_win.clear();

	_printBoard();
	_printSnake();
	_printFood();

	// logDebug("NibblerSFML::draw : " + _toString());

	_win.display();
	return true;
}

void	NibblerSFML::_printBoard() {
	sf::Color color[2] = {
		sf::Color(0x252526FF),		// #252526ff
		sf::Color(0x1E1E1EFF),		// #1E1E1Eff
	};

	sf::RectangleShape rect(sf::Vector2f(_h_margin * 2 + gameInfo->gameboard.x * _h_block,
	_w_margin * 2 + gameInfo->gameboard.y * _w_block));
	rect.setPosition(0, 0);
	rect.setFillColor(sf::Color(0x587C0CFF));
	_win.draw(rect);

	rect.setSize(sf::Vector2f(_w_block, _h_block));
	for (int j = 0; j < gameInfo->gameboard.y; j++) {
		for (int i = 0; i < gameInfo->gameboard.x; i++) {
			rect.setPosition(_w_margin + _w_block * i, _h_margin + _h_block * j);
			rect.setFillColor(color[(i+j) % 2]);
			_win.draw(rect);
		}
	}
}

void	NibblerSFML::_printSnake() {
	sf::RectangleShape rect(sf::Vector2f(_w_block, _h_block));

	for (auto &&i : gameInfo->snake) {
		rect.setFillColor(sf::Color(0xBD63B9));
		rect.setPosition(_w_margin + _w_block * i.x, _h_margin + _h_block * i.y);
		_win.draw(rect);
	}
}

void	NibblerSFML::_printFood() {
	sf::RectangleShape rect(sf::Vector2f(_w_block, _h_block));

	rect.setFillColor(sf::Color(0xCEAF07FF));

	rect.setPosition(_w_margin + _w_block * gameInfo->food.x, _h_margin + _h_block * gameInfo->food.y);
	_win.draw(rect);
}

std::string	NibblerSFML::_toString() const {
	std::string result = "";

	result += "Gameboard [" + std::to_string(gameInfo->gameboard.x) + ", "
			+ std::to_string(gameInfo->gameboard.y) + "]\n"
			"snake length: " + std::to_string(gameInfo->snake.size()) + "\n"
			"game [";
	switch (gameInfo->play) {
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

	result += _getBoard();

	for (glm::ivec2 const &i : gameInfo->snake) {
		result += ">>" + glm::to_string(i);
	}

	return result;
}

std::string	NibblerSFML::_getBoard() const {
	std::string result;

	for (int j = 0; j < gameInfo->gameboard.y; j++) {
		for (int i = 0; i < gameInfo->gameboard.x; i++) {
			if (std::find(gameInfo->snake.begin(), gameInfo->snake.end(), glm::ivec2(i, j)) != gameInfo->snake.end()) {
				if (gameInfo->food == glm::ivec2(i, j))
					result += COLOR_GREEN "o" COLOR_EOC;
				else if (gameInfo->snake.front() == glm::ivec2(i, j))
					result += COLOR_RED "x" COLOR_EOC;
				else
					result += "x";
			} else if (gameInfo->food == glm::ivec2(i, j))
					result += COLOR_GREEN "o" COLOR_EOC;
			else
				result += "_";
		}
		result += "\n";
	}
	return result;
}


extern "C" {
	ANibblerGui *makeNibblerSFML() {
		return new NibblerSFML();
	}
}
