#include "NibblerSDL.hpp"

NibblerSDL::NibblerSDL() {
}

NibblerSDL::~NibblerSDL() {
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
	return true;
}

bool NibblerSDL::draw() const {
	std::cout << "  ###  " << std::endl;
	std::cout << " #   # " << std::endl;
	std::cout << "#     #" << std::endl;
	std::cout << "#     #" << std::endl;
	std::cout << " #   # " << std::endl;
	std::cout << "  ###  " << std::endl;
	return true;
}

extern "C" {
	NibblerSDL *makeNibblerSDL() {
		return new NibblerSDL();
	}
}
