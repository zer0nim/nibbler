#pragma once

#include <curses.h>
#include "IWindow.hpp"

class Window : public IWindow {
private:
	Window();

protected:
	// Members
	WINDOW *_border;  ///< window to make the border
	WINDOW *_data;  ///< window to draw the game
	int _lines;  ///< lines of the terminal window
	int _cols;  ///< columns of the terminal window
	int _y;  ///< Height position of the window
	int _x;  ///< Width postion of the window
	int _color_pair;  ///< Color of the window (color are defined in NibblerNcurses constructor)

public:
	// Constructors
	explicit Window(int lines, int cols, int y, int x, int color_pair);
	~Window();
	Window(Window const &src);

	// Operators
	Window &operator=(Window const &rhs);
	operator WINDOW* ();

	// Methods
	void draw();
	void touch();
	void input(int key);
};
