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
  _textManager(nullptr),
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
	delete _textManager;
	delete _cubeShader;
	delete _cam;
	delete _textRender;
	delete _skybox;

	// properly quit sdl
	SDL_GL_DeleteContext(_context);
	SDL_DestroyWindow(_win);
    SDL_Quit();
}

NibblerSDL::NibblerSDL(NibblerSDL const &src)
: ANibblerGui() {
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
			_inputsFuncs.at(_event->key.keysym.sym)(input);
		}
	}
}

// -- statics const ------------------------------------------------------------
std::unordered_map<SDL_Keycode, NibblerSDL::InputFuncPtr> const	NibblerSDL::_inputsFuncs {
	{SDLK_ESCAPE, [](ANibblerGui::Input &input) {
		input.quit = true; }},
	{SDLK_SPACE, [](ANibblerGui::Input &input) {
		input.togglePause = true; }},
	{SDLK_UP, [](ANibblerGui::Input &input) {
		input.direction = Direction::MOVE_UP; }},
	{SDLK_RIGHT, [](ANibblerGui::Input &input) {
		input.direction = Direction::MOVE_RIGHT; }},
	{SDLK_DOWN, [](ANibblerGui::Input &input) {
		input.direction = Direction::MOVE_DOWN; }},
	{SDLK_LEFT, [](ANibblerGui::Input &input) {
		input.direction = Direction::MOVE_LEFT; }},
	{SDLK_1, [](ANibblerGui::Input &input) {
		input.loadGuiID = 0; }},
	{SDLK_2, [](ANibblerGui::Input &input) {
		input.loadGuiID = 1; }},
	{SDLK_3, [](ANibblerGui::Input &input) {
		input.loadGuiID = 2; }},
};

// -- c extern -----------------------------------------------------------------
extern "C" {
	ANibblerGui *makeNibblerSDL() {
		return new NibblerSDL();
	}
}
