#include "Window.hpp"

// -- Constructors -------------------------------------------------------------

Window::Window(int hotkey): _hotkey(hotkey) {
}

Window::~Window() {
}

Window::Window(Window const &src) {
	*this = src;
}

// -- Operators ----------------------------------------------------------------

Window &Window::operator=(Window const &rhs) {
	if ( this != &rhs ) {
		_hotkey = rhs._hotkey;
	}
	return *this;
}

// -- Accessors ----------------------------------------------------------------

int		Window::getHotkey() const { return _hotkey; }
