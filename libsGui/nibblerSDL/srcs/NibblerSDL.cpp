#include "NibblerSDL.hpp"
#include "Logging.hpp"

NibblerSDL::NibblerSDL() :
  ANibblerGui(),
  _win(nullptr),
  _event(new SDL_Event()) {
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

NibblerSDL::~NibblerSDL() {
	logInfo("exit SDL");
	delete _event;
	SDL_DestroyWindow(_win);
    SDL_Quit();
}

NibblerSDL::NibblerSDL(NibblerSDL const &src) {
	*this = src;
}

NibblerSDL &NibblerSDL::operator=(NibblerSDL const &rhs) {
	if (this != &rhs) {
		_win = rhs._win;
		_surface = rhs._surface;
		_event = rhs._event;
	}
	return *this;
}

bool NibblerSDL::init(GameInfo &gameInfo) {
	logInfo("loading SDL");

	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		logErr("while loading SDL: " << SDL_GetError());
		SDL_Quit();
		return false;
	}

	_win = SDL_CreateWindow(TITLE, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
	if (_win == nullptr) {
		logErr("while loading SDL: " << SDL_GetError());
		SDL_Quit();
		return false;
	}

	_surface = SDL_GetWindowSurface(_win);
	if (_surface == nullptr) {
		logErr("while loading SDL: " << SDL_GetError());
		SDL_Quit();
		return false;
	}

	this->gameInfo = &gameInfo;

	return true;
}

void NibblerSDL::updateInput() {
	input.direction = Direction::NO_MOVE;
	while (SDL_PollEvent(_event)) {
		if (_event->window.event == SDL_WINDOWEVENT_CLOSE)
			input.quit = true;
		else if (_event->key.type == SDL_KEYDOWN && _event->key.keysym.sym == SDLK_ESCAPE)
			input.quit = true;

		else if (_event->key.type == SDL_KEYDOWN && _event->key.keysym.sym == SDLK_UP)
			input.direction = Direction::MOVE_UP;
		else if (_event->key.type == SDL_KEYDOWN && _event->key.keysym.sym == SDLK_RIGHT)
			input.direction = Direction::MOVE_RIGHT;
		else if (_event->key.type == SDL_KEYDOWN && _event->key.keysym.sym == SDLK_DOWN)
			input.direction = Direction::MOVE_DOWN;
		else if (_event->key.type == SDL_KEYDOWN && _event->key.keysym.sym == SDLK_LEFT)
			input.direction = Direction::MOVE_LEFT;

		else if (_event->key.type == SDL_KEYDOWN && _event->key.keysym.sym == SDLK_1)
			input.loadGuiID = 0;
		else if (_event->key.type == SDL_KEYDOWN && _event->key.keysym.sym == SDLK_2)
			input.loadGuiID = 1;
		else if (_event->key.type == SDL_KEYDOWN && _event->key.keysym.sym == SDLK_3)
			input.loadGuiID = 2;
	}
}

bool NibblerSDL::draw() {
	// clear screen
	SDL_FillRect(_surface, NULL, 0x000000);

	// draw rect on the screen
	SDL_Rect rect = {
		100,
		100,
		10 + 100 * input.direction,
		10 + 100 * (4 - input.direction),
	};
	SDL_FillRect(_surface, &rect, SDL_MapRGB(_surface->format, 255, 0, 0));
	SDL_UpdateWindowSurface(_win);


	std::cout << "NibblerSDL::draw : " << _toString() << std::endl;

	return true;
}

std::string	NibblerSDL::_toString() const {
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

std::string	NibblerSDL::_getBoard() const {
	std::string result;

	for (int j = 0; j < gameInfo->gameboard.y; j++) {
		for (int i = 0; i < gameInfo->gameboard.x; i++) {
			if (std::find(gameInfo->snake.begin(), gameInfo->snake.end(), glm::ivec2(i, j)) != gameInfo->snake.end()) {
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
	ANibblerGui *makeNibblerSDL() {
		return new NibblerSDL();
	}
}
