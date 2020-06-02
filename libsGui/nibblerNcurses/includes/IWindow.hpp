#pragma once

#include <curses.h>

class IWindow {
public:
	// Constructors
	virtual ~IWindow() {};

	// Operators
	virtual operator WINDOW* () = 0;

	// Methods
	virtual void draw() = 0;
	virtual void touch() = 0;
	virtual void input(int key) = 0;
};
