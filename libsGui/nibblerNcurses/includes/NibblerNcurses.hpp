#pragma once

#include <curses.h>
#include <iostream>
#include "ANibblerGui.hpp"

class NibblerNcurses : public ANibblerGui {
	public:
		NibblerNcurses();
		virtual ~NibblerNcurses();
		NibblerNcurses(NibblerNcurses const &src);
		NibblerNcurses &operator=(NibblerNcurses const &rhs);

		virtual bool	init(GameInfo &gameInfo);
		virtual void	updateInput();
		virtual bool	draw();

	private:
		WINDOW *		_win;
		std::string		_toString() const;
		std::string		_getBoard() const;
};

class Window {
protected:
	// Members
	int		_hotkey;

public:
	// Constructors
	Window();
	explicit Window(int _hotkey);
	~Window();
	Window(Window const &src);

	// Operators
	Window &operator=(Window const &rhs);
	virtual operator WINDOW* () = 0;

	// Accessors
	int		getHotkey() const;
};

class BorderWindow : public Window {
protected:
	// Members
	WINDOW *_border, *_data;
	int _lines, _cols;
	int _y, _x;
	int _color_pair;

public:
	// Constructors
	BorderWindow();
	explicit BorderWindow(int lines, int cols, int y, int x, int color_pair,
		int hotkey);
	~BorderWindow();
	BorderWindow(BorderWindow const &src);

	// Operators
	BorderWindow &operator=(BorderWindow const &rhs);
	operator WINDOW* ();
};
