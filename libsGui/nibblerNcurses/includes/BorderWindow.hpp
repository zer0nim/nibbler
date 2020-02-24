#pragma once

#include <curses.h>
#include "Window.hpp"

class BorderWindow : public Window {
private:
	BorderWindow();

protected:
	// Members
	WINDOW *_border, *_data;
	int _lines, _cols;
	int _y, _x;
	int _color_pair;

public:
	// Constructors
	explicit BorderWindow(int lines, int cols, int y, int x, int color_pair,
		int hotkey);
	~BorderWindow();
	BorderWindow(BorderWindow const &src);

	// Operators
	BorderWindow &operator=(BorderWindow const &rhs);
	operator WINDOW* ();

	// Methods
	void draw();
	void touch();
	void input(int key);
	// void move_relative(int yoff, int xoff);
};
