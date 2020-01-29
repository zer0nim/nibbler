#include "NibblerSDL.hpp"

NibblerSDL::NibblerSDL() :
  _win(nullptr),
  _event(new SDL_Event()) {}

NibblerSDL::~NibblerSDL() {
	std::cout << "[INFO]: exit SDL" << std::endl;
	SDL_DestroyWindow(_win);
    SDL_Quit();
}

NibblerSDL::NibblerSDL(NibblerSDL const &src) {
	*this = src;
}

NibblerSDL &NibblerSDL::operator=(NibblerSDL const &rhs) {
	(void)rhs;
	// if (this != &rhs)
	// 	;
	return *this;
}

bool NibblerSDL::init() {
	std::cout << "[INFO]: loading SDL" << std::endl;

    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cout << "[ERROR]: while loading SDL" << SDL_GetError() << std::endl;
        SDL_Quit();
		return false;
    }

	_win = SDL_CreateWindow("Nibbler", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		WIDTH, HEIGHT, SDL_WINDOW_SHOWN);

	if (_win == nullptr) {
        std::cout << "[ERROR]: while loading SDL" << SDL_GetError() << std::endl;
		SDL_Quit();
		return false;
	}

    return true;
}

Input::eInput NibblerSDL::getInput() const {
	SDL_PollEvent(_event);

	if(_event->window.event == SDL_WINDOWEVENT_CLOSE)
		return Input::QUIT;
	return Input::NOTHING;
}

bool NibblerSDL::draw() const {
	std::cout << "draw" << std::endl;
	return true;
}

extern "C" {
	NibblerSDL *makeNibblerSDL() {
		return new NibblerSDL();
	}
}
