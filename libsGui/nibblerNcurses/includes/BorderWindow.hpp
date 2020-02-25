#pragma once

#include <curses.h>
#include "IWindow.hpp"

class BorderWindow : public IWindow {
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
	explicit BorderWindow(int lines, int cols, int y, int x, int color_pair);
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
