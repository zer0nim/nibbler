#pragma once

#define C_VAO_WIDTH 4
#define C_NB_FACES 6
// C_VAO_WIDTH * C_NB_FACES
#define C_FACE_A_SIZE 42

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>
#include <array>

#include <map>

#include "ANibblerGui.hpp"
#include "Shader.hpp"
#include "Camera.hpp"
#include "TextRender.hpp"
#include "Skybox.hpp"
#include "TextureManager.hpp"

class NibblerSDL : public ANibblerGui {
	public:
		NibblerSDL();
		virtual ~NibblerSDL();
		NibblerSDL(NibblerSDL const &src);
		NibblerSDL &operator=(NibblerSDL const &rhs);

		virtual bool	init(GameInfo &gameInfo);
		virtual void	updateInput();
		virtual bool	draw();

	private:
		SDL_Window *	_win;
		SDL_Event *		_event;
		SDL_GLContext	_context;
		uint64_t		_lastLoopMs;

		TextureManager		*_textureManager;
		Shader				*_cubeShader;
		Camera				*_cam;
		TextRender			*_textRender;
		Skybox				*_skybox;

		uint32_t			_cubeShVao;
		uint32_t			_cubeShVbo;
		glm::mat4			_projection;

		static std::array<float, C_FACE_A_SIZE> const		_cubeFaces;
		typedef void (*InputFuncPtr)(Input &input);
		static std::map<SDL_Keycode, InputFuncPtr> const	_inputsFuncs;

		bool	_init();
		bool	_initOpengl();
		bool	_initShaders();
		void	_drawBoard();
		void	_drawSnake();
		void	_drawFood();
		void	_drawSkybox(glm::mat4 &view);
		std::chrono::milliseconds	_getMs() const;
};
