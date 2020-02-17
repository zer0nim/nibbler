#include "NibblerSDL.hpp"
#include "Logging.hpp"

// -- init ---------------------------------------------------------------------
bool NibblerSDL::init(GameInfo &gameInfo) {
	this->gameInfo = &gameInfo;

	logInfo("loading SDL");

	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		logErr("while loading SDL: " << SDL_GetError());
		SDL_Quit();
		return false;
	}

	// create window and init opengl settings
	if (!_initOpengl()) {
		return false;
	}

	// init shaders attributes
	if (!_initShaders()) {
		return false;
	}

	return true;
}

// -- _initOpengl --------------------------------------------------------------
bool	NibblerSDL::_initOpengl() {
	// opengl version 4.1
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

	// enable double buffering
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

	// create window
	_win = SDL_CreateWindow("nibbler OpenGL", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		gameInfo->windowSize.x, gameInfo->windowSize.y, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);
	if (_win == nullptr) {
		logErr("while loading OpenGL: " << SDL_GetError());
		return false;
	}

	// create opengl context
	_context = SDL_GL_CreateContext(_win);
	if (_context == 0) {
		logErr("while loading OpenGL: " << SDL_GetError());
		return false;
	}
	// init glad
	if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress)) {
		logErr("while loading OpenGL: failed to init glad");
		return false;
	}

	glEnable(GL_MULTISAMPLE);  // anti aliasing
	glEnable(GL_CULL_FACE);  // face culling
	glEnable(GL_BLEND);  // enable blending (used in textRender)
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_DEPTH_TEST);
	return true;
}

// -- _initShaders -------------------------------------------------------------
bool	NibblerSDL::_initShaders() {
	// create opengl shader stuffs here (buffers, camera, ...)

	// create shader
	_cubeShader = new Shader("./libsGui/nibblerSDL/shaders/cube_vs.glsl",
		"./libsGui/nibblerSDL/shaders/cube_fs.glsl",
		"./libsGui/nibblerSDL/shaders/cube_gs.glsl");
	_cubeShader->use();

	// create and bind vao and vbo
	glGenVertexArrays(1, &_cubeShVao);
	glBindVertexArray(_cubeShVao);
	glGenBuffers(1, &_cubeShVbo);
	glBindBuffer(GL_ARRAY_BUFFER, _cubeShVbo);

	// fill buffer
	glBufferData(GL_ARRAY_BUFFER, _cubeFaces.size() * sizeof(float), &_cubeFaces[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	// bottom left corner face pos
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, C_VAO_WIDTH * sizeof(float),
		reinterpret_cast<void*>(0));
	glEnableVertexAttribArray(0);
	// face normal
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, C_VAO_WIDTH * sizeof(float),
		reinterpret_cast<void*>(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	// face id
	glVertexAttribPointer(2, 1, GL_FLOAT, GL_FALSE, C_VAO_WIDTH * sizeof(float),
		reinterpret_cast<void*>(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	_cubeShader->unuse();

	return true;
}


// -- draw ---------------------------------------------------------------------
bool NibblerSDL::draw() {
	return true;
}

// -- statics const ------------------------------------------------------------
// cube faces
std::array<float, C_FACE_SIZE> const	NibblerSDL::_cubeFaces = {
	// bot left corner,		normals,			faceId
	-0.5f, -0.5f, 0.5f,		0.0f, 0.0f, 1.0f,	0,
	0.5f, -0.5f, 0.5f,		1.0f, 0.0f, 0.0f,	1,
	0.5f, 0.5f, -0.5f,		0.0f, 0.0f, -1.0f,	2,
	-0.5f, -0.5f, -0.5f,	-1.0f, 0.0f, 0.0f,	3,
	-0.5f, 0.5f, 0.5f,		0.0f, 1.0f, 0.0f,	4,
	-0.5f, -0.5f, -0.5f,	0.0f, -1.0f, 0.0f,	5,
};
