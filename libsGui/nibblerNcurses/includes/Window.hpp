#pragma once

#include <curses.h>

class Window {
private:
	Window();

protected:
	// Members
	int		_hotkey;

public:
	// Constructors
	explicit Window(int hotkey);
	virtual ~Window();
	Window(Window const &src);

	// Operators
	Window &operator=(Window const &rhs);
	virtual operator WINDOW* () = 0;

	// Accessors
	int		getHotkey() const;

	// Methods
	virtual void draw() = 0;
	virtual void touch() = 0;
	virtual void input(int key) = 0;
};
