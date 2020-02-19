#include "NibblerNcurses.hpp"
#include "Logging.hpp"

NibblerNcurses::NibblerNcurses() :
  ANibblerGui(),
  _win(nullptr) {
	// init logging
	#if DEBUG
		logging.setLoglevel(LOGDEBUG);
		logging.setPrintFileLine(LOGWARN, true);
		logging.setPrintFileLine(LOGERROR, true);
		logging.setPrintFileLine(LOGFATAL, true);
	#else
		logging.setLoglevel(LOGINFO);
	#endif
}

NibblerNcurses::~NibblerNcurses() {
	logInfo("exit SDL");
	delwin(_win);
}

NibblerNcurses::NibblerNcurses(NibblerNcurses const &src) {
	*this = src;
}

NibblerNcurses &NibblerNcurses::operator=(NibblerNcurses const &rhs) {
	if (this != &rhs) {
		_win = rhs._win;
		// _surface = rhs._surface;
		// _event = rhs._event;
	}
	return *this;
}

bool NibblerNcurses::init(GameInfo &gameInfo) {
	logInfo("loading Ncurses");

	// Init Ncurses
	initscr();
	// One-character-a-time.
	cbreak();
	// No echo.
	noecho();
	// Special keys.
	keypad(stdscr, TRUE);

	this->gameInfo = &gameInfo;

	return true;
}

void NibblerNcurses::updateInput() {
	input.direction = Direction::NO_MOVE;
	// todo(ebaudet): get input event here
}

bool NibblerNcurses::draw() {
	std::cout << "NibblerNcurses::draw : " << _toString() << std::endl;

	return true;
}

std::string	NibblerNcurses::_toString() const {
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

std::string	NibblerNcurses::_getBoard() const {
	std::string result;

	for (int j = 0; j < gameInfo->gameboard.y; j++) {
		for (int i = 0; i < gameInfo->gameboard.x; i++) {
			if (std::find(gameInfo->snake.begin(), gameInfo->snake.end(), glm::ivec2(i, j))
					!= gameInfo->snake.end()) {
				if (gameInfo->food == glm::ivec2(i, j))
					result += LOG_COL_GREEN "o" LOG_COL_EOC;
				else if (gameInfo->snake.front() == glm::ivec2(i, j))
					result += LOG_COL_RED "x" LOG_COL_EOC;
				else
					result += "x";
			} else if (gameInfo->food == glm::ivec2(i, j))
					result += LOG_COL_GREEN "o" LOG_COL_EOC;
			else
				result += "_";
		}
		result += "\n";
	}
	return result;
}


extern "C" {
	ANibblerGui *makeNibblerNcurses() {
		return new NibblerNcurses();
	}
}
