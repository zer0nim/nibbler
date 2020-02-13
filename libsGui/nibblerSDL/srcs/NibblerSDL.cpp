#include "NibblerSDL.hpp"
#include "Logging.hpp"

// -- help functions -----------------------------------------------------------
std::chrono::milliseconds getMs() {
	return std::chrono::duration_cast<std::chrono::milliseconds>(
		std::chrono::system_clock::now().time_since_epoch());
}

// -- NibblerSDL ---------------------------------------------------------------
NibblerSDL::NibblerSDL() :
  ANibblerGui(),
  _win(nullptr),
  _event(new SDL_Event()),
  _context(0),
  _lastLoopMs(0),
  _cubeShader(nullptr),
  _cam(nullptr),
  _textRender(nullptr),
  _skybox(nullptr) {
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
	delete _cubeShader;
	delete _cam;
	delete _textRender;
	delete _skybox;
	SDL_GL_DeleteContext(_context);
	SDL_DestroyWindow(_win);
    SDL_Quit();
}

NibblerSDL::NibblerSDL(NibblerSDL const &src) {
	*this = src;
}

NibblerSDL &NibblerSDL::operator=(NibblerSDL const &rhs) {
	if (this != &rhs) {
		logErr("The copy operator should not be called")
	}
	return *this;
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

// -- c extern -----------------------------------------------------------------
extern "C" {
	ANibblerGui *makeNibblerSDL() {
		return new NibblerSDL();
	}
}
