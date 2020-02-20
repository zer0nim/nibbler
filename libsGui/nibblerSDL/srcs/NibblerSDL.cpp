#include "NibblerSDL.hpp"
#include "Logging.hpp"

// -- NibblerSDL ---------------------------------------------------------------
NibblerSDL::NibblerSDL() :
  ANibblerGui(),
  _win(nullptr),
  _event(new SDL_Event()),
  _context(0),
  _lastLoopMs(0),
  _dtTime(0),
  _textureManager(nullptr),
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

	// enable cursor
	SDL_ShowCursor(SDL_ENABLE);
	SDL_SetRelativeMouseMode(SDL_FALSE);

	// free vao / vbo
	_cubeShader->use();
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	glDeleteBuffers(1, &_cubeShVbo);
	glDeleteVertexArrays(1, &_cubeShVao);
	_cubeShader->unuse();

	delete _event;
	delete _textureManager;
	delete _cubeShader;
	delete _cam;
	delete _textRender;
	delete _skybox;

	// properly quit sdl
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
	uint64_t time = _getMs().count();
	_dtTime = (time - _lastLoopMs) / 1000.0;
	_lastLoopMs = time;

	// reset inputs
	input.togglePause = false;

	input.direction = Direction::NO_MOVE;
	while (SDL_PollEvent(_event)) {
		// close button
		if (_event->window.event == SDL_WINDOWEVENT_CLOSE) {
			input.quit = true;
		}

		// key release
		if (_event->key.type == SDL_KEYDOWN &&
			_inputsFuncs.find(_event->key.keysym.sym) != _inputsFuncs.end()) {
			_inputsFuncs.at(_event->key.keysym.sym)(input, gameInfo);
		}

		// mouse motion
		if (_event->type == SDL_MOUSEMOTION) {
			_cam->processMouseMovement(_event->motion.xrel, -_event->motion.yrel);
		}
	}

	// get curently pressed keys
	const Uint8 * keystates = SDL_GetKeyboardState(NULL);
	// camera movement
	bool isRun = keystates[SDL_SCANCODE_LSHIFT];
	if (keystates[SDL_SCANCODE_W]) {
		_cam->processKeyboard(CamMovement::Forward, _dtTime, isRun);
	}
	if (keystates[SDL_SCANCODE_D]) {
		_cam->processKeyboard(CamMovement::Right, _dtTime, isRun);
	}
	if (keystates[SDL_SCANCODE_S]) {
		_cam->processKeyboard(CamMovement::Backward, _dtTime, isRun);
	}
	if (keystates[SDL_SCANCODE_A]) {
		_cam->processKeyboard(CamMovement::Left, _dtTime, isRun);
	}
	if (keystates[SDL_SCANCODE_Q]) {
		_cam->processKeyboard(CamMovement::Down, _dtTime, isRun);
	}
	if (keystates[SDL_SCANCODE_E]) {
		_cam->processKeyboard(CamMovement::Up, _dtTime, isRun);
	}
}

// -- statics const ------------------------------------------------------------
std::unordered_map<SDL_Keycode, NibblerSDL::InputFuncPtr> const	NibblerSDL::_inputsFuncs {
	{SDLK_ESCAPE, [](ANibblerGui::Input &input, GameInfo const *gameInfo) {
		(void)gameInfo;
		input.quit = true; }},
	{SDLK_SPACE, [](ANibblerGui::Input &input, GameInfo const *gameInfo) {
		(void)gameInfo;
		input.togglePause = true; }},
	{SDLK_RIGHT, [](ANibblerGui::Input &input, GameInfo const *gameInfo) {
		if (gameInfo->direction != Direction::NO_MOVE) {
			uint8_t dir = (gameInfo->direction + 1) % 5;
			if (dir == 0) {
				dir = 1;
			}
			input.direction = static_cast<Direction::Enum>(dir);
		}
	}},
	{SDLK_LEFT, [](ANibblerGui::Input &input, GameInfo const *gameInfo) {
		if (gameInfo->direction != Direction::NO_MOVE) {
			uint8_t dir = (gameInfo->direction - 1) % 5;
			if (dir == 0) {
				dir = 4;
			}
			input.direction = static_cast<Direction::Enum>(dir);
		}
	}},
	{SDLK_1, [](ANibblerGui::Input &input, GameInfo const *gameInfo) {
		(void)gameInfo;
		input.loadGuiID = 0; }},
	{SDLK_2, [](ANibblerGui::Input &input, GameInfo const *gameInfo) {
		(void)gameInfo;
		input.loadGuiID = 1; }},
	{SDLK_3, [](ANibblerGui::Input &input, GameInfo const *gameInfo) {
		(void)gameInfo;
		input.loadGuiID = 2; }},
};

// -- c extern -----------------------------------------------------------------
extern "C" {
	ANibblerGui *makeNibblerSDL() {
		return new NibblerSDL();
	}
}
