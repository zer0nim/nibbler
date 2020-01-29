#pragma once

#include <SDL2/SDL.h>
#include <iostream>
#include "INibblerGui.hpp"

#define WIDTH 800
#define HEIGHT 600

class NibblerSDL : public INibblerGui {
	public:
		NibblerSDL();
		virtual ~NibblerSDL();
		NibblerSDL(NibblerSDL const &src);
		NibblerSDL &operator=(NibblerSDL const &rhs);

		virtual bool			init();
		virtual Input::eInput	getInput() const;
		virtual bool			draw() const;

	private:
		SDL_Window *	_win;
		SDL_Event *		_event;
};

typedef NibblerSDL *(*makerNibblerSDL)();
