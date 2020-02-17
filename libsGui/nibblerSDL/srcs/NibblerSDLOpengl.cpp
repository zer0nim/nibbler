#include "NibblerSDL.hpp"

#include "Logging.hpp"
#include "Material.hpp"
#include "debug.hpp"

// -- help functions -----------------------------------------------------------
std::chrono::milliseconds	NibblerSDL::_getMs() const {
	return std::chrono::duration_cast<std::chrono::milliseconds>(
		std::chrono::system_clock::now().time_since_epoch());
}

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

	// disable cursor for fps camera
	SDL_ShowCursor(SDL_DISABLE);
	SDL_SetRelativeMouseMode(SDL_TRUE);

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
// create opengl shader stuffs here (buffers, camera, ...)
bool	NibblerSDL::_initShaders() {
	// -- vao vbo --------------------------------------------------------------
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
	glBufferData(GL_ARRAY_BUFFER, _cubeFaces.size() * sizeof(float),
		&_cubeFaces[0], GL_STATIC_DRAW);

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

	// unbind vao / vbo
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	// -- camera ---------------------------------------------------------------
	_cam = new Camera(glm::vec3(0, 5, -5), glm::vec3(0, 1, 0));

	float angle = _cam->zoom;
	float ratio = static_cast<float>(gameInfo->windowSize.x) / gameInfo->windowSize.y;
	float nearD = 0.1f;
	float farD = 400;
	_projection = glm::perspective(glm::radians(angle), ratio, nearD, farD);

	// -- set default uniforms -------------------------------------------------
	// projection
	_cubeShader->setMat4("projection", _projection);

	// cube material
	Material material;
	_cubeShader->setVec3("material.specular", material.specular);
	_cubeShader->setFloat("material.shininess", material.shininess);

	// direction light
	_cubeShader->setVec3("dirLight.direction", -0.2f, -0.8f, 0.6f);
	_cubeShader->setVec3("dirLight.ambient", 0.4f, 0.4f, 0.4f);
	_cubeShader->setVec3("dirLight.diffuse", 0.8f, 0.8f, 0.8f);
	_cubeShader->setVec3("dirLight.specular", 0.1f, 0.1f, 0.1f);

	// point light
	_cubeShader->setFloat("pointLight.constant", 1.0f);
	_cubeShader->setFloat("pointLight.linear", 0.09f);
	_cubeShader->setFloat("pointLight.quadratic", 0.032f);

	_cubeShader->setVec3("pointLight.ambient", 0.4f, 0.4f, 0.4f);
	_cubeShader->setVec3("pointLight.diffuse", 0.8f, 0.8f, 0.8f);
	_cubeShader->setVec3("pointLight.specular", 0.1f, 0.1f, 0.1f);
	// disabled for now
	_cubeShader->setBool("pointLight.enabled", false);

	// disable texture transparency for now
	_cubeShader->setBool("enableTransparency", false);

	_cubeShader->unuse();

	// -- skybox ---------------------------------------------------------------
	_skybox = new Skybox;
	_skybox->getShader().use();
	_skybox->getShader().setMat4("projection", _projection);
	_skybox->getShader().unuse();

	// -------------------------------------------------------------------------
	_lastLoopMs = _getMs().count();  // init first frame

	return true;
}


// -- draw ---------------------------------------------------------------------
bool NibblerSDL::draw() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glViewport(0, 0, gameInfo->windowSize.x, gameInfo->windowSize.y);
	glClearColor(0.11373f, 0.17647f, 0.27059f, 1.0f);

	glm::mat4	view = _cam->getViewMatrix();
	_cubeShader->use();
	_cubeShader->setMat4("view", view);
	_cubeShader->setVec3("viewPos", _cam->pos);
	glBindVertexArray(_cubeShVao);
	_cubeShader->unuse();

	// -- drawing --------------------------------------------------------------
	_cubeShader->use();
	glm::mat4 model(1.0);
	glm::vec3 pos = glm::vec3(0.0, 0.0, 0.0);

	// draw cube
	model = glm::translate(glm::mat4(1.0), pos);
	_cubeShader->setMat4("model", model);
	glDrawArrays(GL_POINTS, 0, C_NB_FACES);
	_cubeShader->unuse();

	// draw skybox
	CAMERA_MAT4	skyView = view;
	skyView[3][0] = 0;  // remove translation for the skybox
	skyView[3][1] = 0;
	skyView[3][2] = 0;
	_skybox->getShader().use();
	_skybox->getShader().setMat4("view", skyView);
	_skybox->getShader().unuse();
	_skybox->draw(0.5);

	// swap buffer and check errors
	SDL_GL_SwapWindow(_win);
	checkError();
	return true;
}

// -- statics const ------------------------------------------------------------
// cube faces
std::array<float, C_FACE_A_SIZE> const	NibblerSDL::_cubeFaces = {
	// bot left corner,		normals,			faceId
	-0.5f, -0.5f, 0.5f,		0.0f, 0.0f, 1.0f,	0,
	0.5f, -0.5f, 0.5f,		1.0f, 0.0f, 0.0f,	1,
	0.5f, 0.5f, -0.5f,		0.0f, 0.0f, -1.0f,	2,
	-0.5f, -0.5f, -0.5f,	-1.0f, 0.0f, 0.0f,	3,
	-0.5f, 0.5f, 0.5f,		0.0f, 1.0f, 0.0f,	4,
	-0.5f, -0.5f, -0.5f,	0.0f, -1.0f, 0.0f,	5,
};
