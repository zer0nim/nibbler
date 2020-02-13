#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>
#include "ANibblerGui.hpp"
#include "Shader.hpp"
#include "Camera.hpp"
#include "TextRender.hpp"
#include "Skybox.hpp"

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

		Shader				*_cubeShader;
		Camera				*_cam;
		TextRender			*_textRender;
		Skybox				*_skybox;

		uint32_t			_cubeShaderVAO;
		uint32_t			_cubeShaderVBO;
		static const float	_cubeVertices[];
		glm::mat4			_projection;

		bool	_init();
		bool	_initOpengl();
		bool	_initShaders();
};
