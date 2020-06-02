#include <new>
#include <csignal>

// glm
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>
#include <glm/gtx/string_cast.hpp>  // to print vect/mat with glm::to_string

#include "NibblerNcurses.hpp"
#include "Logging.hpp"

// -- Static members initialisation --------------------------------------------

std::map<int , NibblerNcurses::inputFuncPtr>	NibblerNcurses::_inputKeyPressed = {
	{27, [](Input &input, NibblerNcurses &inst) { (void)inst; input.quit = true; }},
	{32, [](Input &input, NibblerNcurses &inst) { if (inst.drawable) input.togglePause = true; }},

	{KEY_UP, [](Input &input, NibblerNcurses &inst) { if (inst.drawable) input.direction = Direction::MOVE_UP; }},
	{KEY_RIGHT, [](Input &input, NibblerNcurses &inst) { if (inst.drawable) input.direction = Direction::MOVE_RIGHT; }},
	{KEY_DOWN, [](Input &input, NibblerNcurses &inst) { if (inst.drawable) input.direction = Direction::MOVE_DOWN; }},
	{KEY_LEFT, [](Input &input, NibblerNcurses &inst) { if (inst.drawable) input.direction = Direction::MOVE_LEFT; }},

	{49, [](Input &input, NibblerNcurses &inst) { (void)inst; input.loadGuiID = 0; }},
	{50, [](Input &input, NibblerNcurses &inst) { (void)inst; input.loadGuiID = 1; }},
	{51, [](Input &input, NibblerNcurses &inst) { (void)inst; input.loadGuiID = 2; }},

	{KEY_RESIZE, [](Input &input, NibblerNcurses &inst) { (void)input; inst.resize(); }},
};

// -- Constructors -------------------------------------------------------------

/**
 * @brief Construct a new NibblerNcurses::NibblerNcurses object
 */
NibblerNcurses::NibblerNcurses() :
  ANibblerGui() {
	_win = nullptr;
	_win_size = {0, 0};
	_tail = {0, 0};

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
	init_pair(1, COLOR_WHITE, COLOR_BLACK);		// text
	init_pair(2, COLOR_WHITE, COLOR_MAGENTA); 	// background
	init_pair(3, COLOR_BLACK, COLOR_WHITE);		// snake
	init_pair(4, COLOR_YELLOW, COLOR_BLUE);		// food

	curs_set(0);  // no cursors on screen
}

/**
 * @brief Destroy the NibblerNcurses::NibblerNcurses object
 */
NibblerNcurses::~NibblerNcurses() {
	endwin();
	logInfo("exit Ncurses");
	if (_win)
		delete _win;
}

/**
 * @brief Construct a new NibblerNcurses::NibblerNcurses object
 *
 * @param src object to copy
 */
NibblerNcurses::NibblerNcurses(NibblerNcurses const &src)
: ANibblerGui() {
	logWarn("NibblerNcurses copy operator called !!!");
	*this = src;
}

// -- Operators ----------------------------------------------------------------

/**
 * @brief Copy this object
 *
 * @param rhs The object to copy
 * @return NibblerNcurses& A reference to the copied object
 */
NibblerNcurses &NibblerNcurses::operator=(NibblerNcurses const &rhs) {
	if (this != &rhs) {
		_win = rhs._win;
		_win_size = rhs._win_size;
		_tail = rhs._tail;
		_state = rhs._state;
	}
	return *this;
}

// -- Public Methods -----------------------------------------------------------

/**
 * @brief Init the library
 *
 * @param gameInfo reference th gameInfo object
 * @return true if the init succeed
 * @return false
 */
bool NibblerNcurses::init(GameInfo &gameInfo) {
	logInfo("loading Ncurses");

	this->gameInfo = &gameInfo;
	resize();

	return true;
}

/**
 * @brief Method to update the input pressed
 */
void NibblerNcurses::updateInput() {
	input.direction = Direction::NO_MOVE;
	input.togglePause = false;

	int c = _win ? wgetch(*_win) : getch();

	if (_inputKeyPressed.find(c) != _inputKeyPressed.end()) {
		_inputKeyPressed[c](input, *this);
	}
}

/**
 * @brief Draw is called each frame
 *
 * @return true if succeed
 * @return false if failure
 */
bool NibblerNcurses::draw() {
	move(0, 0);

	_touchAll();
	_drawAll();

	if (drawable && _win) {
		// clean board after a Game Over
		if (_state == State::S_GAMEOVER && gameInfo->play == State::S_PAUSE) {
			for (int i = 0; i < gameInfo->gameboard.y; i++) {
				for (int j = 0; j < (gameInfo->gameboard.x * 2); j++) {
					mvwaddch(*_win, i, j, ' ' | COLOR_PAIR(2));
				}
			}
		}
		// clean snake tail
		mvwaddch(*_win, _tail.y, 2 * _tail.x, ' ' | COLOR_PAIR(2));
		mvwaddch(*_win, _tail.y, 2 * _tail.x + 1, ' ' | COLOR_PAIR(2));
		// print snake
		for (auto &&snake : gameInfo->snake) {
			char c = ' ';
			if (snake == gameInfo->snake[0]) {
				c = '^';
				if (gameInfo->play == State::S_GAMEOVER)
					c = 'X';
			}
			mvwaddch(*_win, snake.y, snake.x * 2, c | COLOR_PAIR(3));
			mvwaddch(*_win, snake.y, snake.x * 2 + 1, c | COLOR_PAIR(3));
		}
		_tail = gameInfo->snake.back();
		// print food
		mvwaddch(*_win, gameInfo->food.y, 2 * gameInfo->food.x, ' ' | COLOR_PAIR(4));
		mvwaddch(*_win, gameInfo->food.y, 2 * gameInfo->food.x + 1, ' ' | COLOR_PAIR(4));

		// print text
		std::string str;
		int length = gameInfo->gameboard.x * 2 - 1;
		if (gameInfo->play == State::S_PAUSE)
			str = _center("Pause | " + std::to_string(gameInfo->score), length);
		else if (gameInfo->play == State::S_GAMEOVER)
			str = _center("Game Over :( | " + std::to_string(gameInfo->score), length);
		else
			str = _center("score: " + std::to_string(gameInfo->score), length);

		int		i = 0;
		for (auto it = str.begin(); it != str.end(); ++it) {
			mvwaddch(*_win, gameInfo->gameboard.y, i, *it | COLOR_PAIR(1));
			++i;
		}
	}

	doupdate();

	// save state
	_state = gameInfo->play;

	return true;
}

/**
 * @brief Called when window is resized
 */
void	NibblerNcurses::resize() {
	logInfo("resize Ncurses");
	getmaxyx(stdscr, _win_size.y, _win_size.x);

	glm::ivec2 expected_game = {(gameInfo->gameboard.x * 2) + 2, gameInfo->gameboard.y + 3};

	if (expected_game.y > _win_size.y || expected_game.x > _win_size.x) {
		// too small
		if (gameInfo->play == State::S_PLAY)
			input.togglePause = true;

		_state = gameInfo->play;
		if (_win)
			delete _win;

		_win = new Window(_win_size.y, _win_size.x, 0, 0, 1);
		nodelay(*_win, TRUE);		// to have a non blocking getch.

		_touchAll();
		_drawAll();

		std::string str = "change size | "
			+ std::to_string(_win_size.y) + "x" + std::to_string(_win_size.x)
			+ " => " + std::to_string(expected_game.y) + "x"
			+ std::to_string(expected_game.x);
		if ((_win_size.x - 3) < static_cast<int>(str.length()))
			str = str.substr(std::string("change size | ").length());
		if ((_win_size.x - 3) < static_cast<int>(str.length()))
			str = "...";
		if ((_win_size.x - 3) < static_cast<int>(str.length()))
			str = str.substr(str.length() - (_win_size.x - 3));
		str = _center(str, _win_size.x - 2);

		mvwinsstr(*_win, _win_size.y / 2 - 1, 0, str.c_str());

		doupdate();
		drawable = false;
	} else {
		// Correct size
		drawable = true;
		if (_win)
			delete _win;
		_win = new Window(
			expected_game.y,
			expected_game.x,
			_win_size.y / 2 - expected_game.y / 2,
			_win_size.x / 2 - expected_game.x / 2,
			2);
		nodelay(*_win, TRUE);		// to have a non blocking getch.
		_touchAll();
	}
}

// -- Private Methods ----------------------------------------------------------

/**
 * @brief Center a string in a defined width
 *
 * @param input the string to center
 * @param width the final width
 * @return std::string the centered string
 */
std::string		NibblerNcurses::_center(std::string input, int width) {
	int left = (width - input.length()) / 2;
	int right = width - left - input.length();
	return std::string(left, ' ') + input + std::string(right, ' ');
}

/**
 * @brief Touch all windows
 */
void NibblerNcurses::_touchAll() {
	touchwin(stdscr);
	_win->touch();
}

/**
 * @brief Draw all windows
 */
void NibblerNcurses::_drawAll() {
	wnoutrefresh(stdscr);
	_win->draw();
}

// -- Exceptions errors --------------------------------------------------------

NibblerNcurses::NibblerNcursesException::NibblerNcursesException()
: std::runtime_error("NibblerNcurses Exception") {}

NibblerNcurses::NibblerNcursesException::NibblerNcursesException(const char* what_arg)
: std::runtime_error(std::string(std::string("NibblerNcursesError: ") + what_arg).c_str()) {}

// -- Library external access functions ----------------------------------------

/**
 * @brief Function of the lib that can be externally called
 */
extern "C" {
	/**
	 * @brief Allow to create a new NibblerNcurses object
	 *
	 * @return ANibblerGui* new object created
	 */
	ANibblerGui *makeNibblerNcurses() {
		return new NibblerNcurses();
	}
}
