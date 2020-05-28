#include "Window.hpp"

// -- Constructors -------------------------------------------------------------

/**
 * @brief Construct a new Window::Window object
 *
 * @param lines Window height
 * @param cols Window width
 * @param y Window position height
 * @param x Window position width
 * @param color_pair Window color
 */
Window::Window(int lines, int cols, int y, int x, int color_pair)
: IWindow(),
_lines(lines), _cols(cols), _y(y), _x(x), _color_pair(color_pair) {
	// make a window just to make the border
	_border = newwin(lines, cols, y, x);
	wcolor_set(_border, color_pair, NULL);  // use color defined
	wattron(_border, A_BOLD); 	// bold chars
	box(_border, 0, 0);			// draw the border, inside win
	wnoutrefresh(_border);		// display it

	// make an inside window
	_data = newwin(lines-2, cols-2, y+1, x+1);
	wcolor_set(_data, color_pair, NULL);  // use color defined
	wbkgdset(_data, ' ' | A_BOLD | COLOR_PAIR(color_pair));

	wclear(_data);				// start with a fresh blue bkgd
	wnoutrefresh(_data);		// display it

	scrollok(_data, TRUE);		// allow scrolling in data win
	keypad(_data, TRUE);		// interpret function keys for us
}

/**
 * @brief Destroy the Window::Window object
 */
Window::~Window() {
	delwin(_data);
	delwin(_border);
}

/**
 * @brief Construct a new Window::Window object
 *
 * @param src object to copy
 */
Window::Window(Window const &src) {
	*this = src;
}

// -- Operators ----------------------------------------------------------------

/**
 * @brief Copy the object
 *
 * @param rhs The object to copy
 * @return Window& A reference to the copied object
 */
Window &Window::operator=(Window const &rhs) {
	if ( this != &rhs ) {
		_border = rhs._border;
		_data = rhs._data;
		_lines = rhs._lines;
		_cols = rhs._cols;
		_y = rhs._y;
		_x = rhs._x;
		_color_pair = rhs._color_pair;
	}
	return *this;
}

/**
 * @brief Overload operator WINDOW
 *
 * @return WINDOW* window which draw the game
 */
Window::operator WINDOW* () {
	// pass back the data window, since that the usual one for IO
	return _data;
}

// -- Methods ------------------------------------------------------------------

/**
 * @brief Draw method. Called each frames
 */
void	Window::draw() {
	wnoutrefresh(_border);
	wnoutrefresh(_data);
}

/**
 * @brief Touch method
 */
void	Window::touch() {
	touchwin(_border);
	touchwin(_data);
}

/**
 * @brief Input method
 *
 * @param key
 */
void	Window::input(int key) {
	waddch(_data, key);
}

