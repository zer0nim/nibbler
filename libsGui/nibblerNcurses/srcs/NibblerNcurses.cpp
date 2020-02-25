#include <new>
#include <csignal>
#include "NibblerNcurses.hpp"
#include "Logging.hpp"

// -- Static members initialisation --------------------------------------------

std::map<int , NibblerNcurses::inputFuncPtr>	NibblerNcurses::_inputKeyPressed = {
	{27, [](Input &input) { input.quit = true;} },
	{32, [](Input &input) { input.togglePause = true; } },

	{KEY_UP, [](Input &input) { input.direction = Direction::MOVE_UP; } },
	{KEY_RIGHT, [](Input &input) { input.direction = Direction::MOVE_RIGHT; } },
	{KEY_DOWN, [](Input &input) { input.direction = Direction::MOVE_DOWN; } },
	{KEY_LEFT, [](Input &input) { input.direction = Direction::MOVE_LEFT; } },

	{49, [](Input &input) { input.loadGuiID = 0; } },
	{50, [](Input &input) { input.loadGuiID = 1; } },
	{51, [](Input &input) { input.loadGuiID = 2; } },
};

// -- Constructors -------------------------------------------------------------

NibblerNcurses::NibblerNcurses() :
  ANibblerGui() {
	// init logging
	#if DEBUG
		logging.setLoglevel(LOGDEBUG);
		logging.setPrintFileLine(LOGWARN, true);
		logging.setPrintFileLine(LOGERROR, true);
		logging.setPrintFileLine(LOGFATAL, true);
	#else
		logging.setLoglevel(LOGINFO);
	#endif

	// standard ncurses init
	initscr();
	start_color();
	cbreak(); noecho();		// character-at-a-time input, no echo
	nonl();
	intrflush(stdscr, FALSE);
	keypad(stdscr, TRUE);		// interpret function keys for us

	// set color pair for the board, the snake and the food.
	init_pair(1, COLOR_YELLOW, COLOR_BLUE);
	init_pair(2, COLOR_BLACK, COLOR_WHITE);
	init_pair(3, COLOR_WHITE, COLOR_MAGENTA);
	init_pair(4, COLOR_WHITE, COLOR_BLACK);

	curs_set(0);  // no cursors on screen
}

NibblerNcurses::~NibblerNcurses() {
	endwin();
	logInfo("exit Ncurses");
	if (_stack.size() >= 0) {
		stack_type::iterator beg = _stack.begin(), end = _stack.end();
		for (; beg != end; ++beg) {
			delete *beg;
		}
		_stack.clear();
	}
}

NibblerNcurses::NibblerNcurses(NibblerNcurses const &src) {
	*this = src;
}

// -- Operators ----------------------------------------------------------------

NibblerNcurses &NibblerNcurses::operator=(NibblerNcurses const &rhs) {
	if (this != &rhs) {
		_stack = rhs._stack;
	}
	return *this;
}

// -- Public Methods -----------------------------------------------------------

bool NibblerNcurses::init(GameInfo &gameInfo) {
	logInfo("loading Ncurses");

	std::signal(SIGWINCH, resizeHandler);

	this->gameInfo = &gameInfo;

	getmaxyx(stdscr, _win.y, _win.x);

	if ((gameInfo.gameboard.y + 2) >= _win.y || ((gameInfo.gameboard.x * 2) + 2) >= _win.x) {
		endwin();
		throw NibblerNcursesException("too short screen for game.");
	}

	Window *win = new BorderWindow(
		gameInfo.gameboard.y + 3,
		gameInfo.gameboard.x * 2 + 2,
		_win.y / 2 - gameInfo.gameboard.y / 2,
		_win.x / 2 - gameInfo.gameboard.x,
		3,
		KEY_F(3)
	);
	try {
		_stack.insert(_stack.begin(), win);
		nodelay(*win, TRUE);		// to have a non blocking getch.
	} catch (std::bad_alloc &e) {
		delete win;
		throw NibblerNcursesException(e.what());
	}

	_touchAll();
	return true;
}

void			NibblerNcurses::resizeHandler(int sig) {
	logFatal("resizeHandler");
	(void)sig;
	int nh, nw;
	getmaxyx(stdscr, nh, nw);  /* get the new screen size */
}

void NibblerNcurses::updateInput() {
	input.direction = Direction::NO_MOVE;
	input.togglePause = false;

	int c = _stack.size() ? wgetch(*_stack[0]) : getch();

	if (_inputKeyPressed.find(c) != _inputKeyPressed.end()) {
		_inputKeyPressed[c](input);
	}
}

bool NibblerNcurses::draw() {
	move(0, 0);
	wnoutrefresh(stdscr);
	for (auto &&it : _stack) {
		it->draw();
	}

	_touchAll();
	wnoutrefresh(*_stack[0]);		// display it

	if (_stack.size()) {
		// clean board after a Game Over
		if (_state == State::S_GAMEOVER && gameInfo->play == State::S_PAUSE) {
			for (int i = 0; i < gameInfo->gameboard.y; i++) {
				for (int j = 0; j < (gameInfo->gameboard.x * 2); j++) {
					mvwaddch(*_stack[0], i, j, ' ' | COLOR_PAIR(3));
				}
			}
		}
		// clean snake tail
		mvwaddch(*_stack[0], _tail.y, 2 * _tail.x, ' ' | COLOR_PAIR(3));
		mvwaddch(*_stack[0], _tail.y, 2 * _tail.x + 1, ' ' | COLOR_PAIR(3));
		// print snake
		for (auto &&snake : gameInfo->snake) {
			char c = ' ';
			if (snake == gameInfo->snake[0]) {
				c = '^';
				if (gameInfo->play == State::S_GAMEOVER)
					c = 'X';
			}
			mvwaddch(*_stack[0], snake.y, snake.x * 2, c | COLOR_PAIR(2));
			mvwaddch(*_stack[0], snake.y, snake.x * 2 + 1, c | COLOR_PAIR(2));
		}
		_tail = gameInfo->snake.back();
		// print food
		mvwaddch(*_stack[0], gameInfo->food.y, 2 * gameInfo->food.x, ' ' | COLOR_PAIR(1));
		mvwaddch(*_stack[0], gameInfo->food.y, 2 * gameInfo->food.x + 1, ' ' | COLOR_PAIR(1));

		wmove(*_stack[0], gameInfo->gameboard.y, 0);

		std::string str;
		int length = gameInfo->gameboard.x * 2 - 1;
		if (gameInfo->play == State::S_PAUSE)
			str = _center("Pause | " + std::to_string(gameInfo->snake.size()), length);
		else if (gameInfo->play == State::S_GAMEOVER)
			str = _center("Game Over :( | " + std::to_string(gameInfo->snake.size()), length);
		else
			str = _center("score: " + std::to_string(gameInfo->snake.size()), length);

		int		i = 0;
		for (auto it = str.begin(); it != str.end(); ++it) {
			mvwaddch(*_stack[0], gameInfo->gameboard.y, i, *it | COLOR_PAIR(4));
			++i;
		}

		wmove(*_stack[0], gameInfo->gameboard.y, gameInfo->gameboard.x * 2 - 1);
	}

	doupdate();

	_state = gameInfo->play;

	return true;
}

// -- Private Methods ----------------------------------------------------------

std::string		NibblerNcurses::_center(std::string input, int width) {
	int left = (width - input.length()) / 2;
	int right = width - left - input.length();
	return std::string(left, ' ') + input + std::string(right, ' ');
}

void NibblerNcurses::_touchAll() {
	touchwin(stdscr);
	for (auto &&it : _stack) {
		it->touch();
	}
}

// -- Exceptions errors --------------------------------------------------------

NibblerNcurses::NibblerNcursesException::NibblerNcursesException()
: std::runtime_error("NibblerNcurses Exception") {}

NibblerNcurses::NibblerNcursesException::NibblerNcursesException(const char* what_arg)
: std::runtime_error(std::string(std::string("NibblerNcursesError: ") + what_arg).c_str()) {}

// -- Library external access functions ----------------------------------------

extern "C" {
	ANibblerGui *makeNibblerNcurses() {
		return new NibblerNcurses();
	}

	// void		*resizeHandler(int sig) {
	// 	int nh, nw;
	// 	getmaxyx(stdscr, nh, nw);  /* get the new screen size */
	// }
}
