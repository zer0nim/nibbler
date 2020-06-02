#include "NibblerSFML.hpp"
#include "Logging.hpp"

// -- Static members initialisation --------------------------------------------

std::map<sf::Keyboard::Key , NibblerSFML::inputFuncPtr>	NibblerSFML::_inputKeyPressed = {
	{sf::Keyboard::Escape, [](Input &input) { input.quit = true; } },
	{sf::Keyboard::Space, [](Input &input) { input.togglePause = true; } },

	{sf::Keyboard::Up, [](Input &input) { input.direction = Direction::MOVE_UP; } },
	{sf::Keyboard::Right, [](Input &input) { input.direction = Direction::MOVE_RIGHT; } },
	{sf::Keyboard::Down, [](Input &input) { input.direction = Direction::MOVE_DOWN; } },
	{sf::Keyboard::Left, [](Input &input) { input.direction = Direction::MOVE_LEFT; } },

	{sf::Keyboard::Num1, [](Input &input) { input.loadGuiID = 0; } },
	{sf::Keyboard::Num2, [](Input &input) { input.loadGuiID = 1; } },
	{sf::Keyboard::Num3, [](Input &input) { input.loadGuiID = 2; } },
};

// -- Constructors -------------------------------------------------------------

/**
 * @brief Construct a new NibblerSFML::NibblerSFML object
 */
NibblerSFML::NibblerSFML() :
  ANibblerGui(),
  _win() {
	// init logging
	#if DEBUG
		logging.setLoglevel(LOGDEBUG);
		logging.setPrintFileLine(LOGWARN, true);
		logging.setPrintFileLine(LOGERROR, true);
		logging.setPrintFileLine(LOGFATAL, true);
	#else
		logging.setLoglevel(LOGINFO);
	#endif

	if (!_font.loadFromFile("assets/fonts/snakebold.ttf"))
		throw NibblerSFMLException("Inexistent font : assets/fonts/snakebold.ttf");

	_block = {10, 10};
	_margin = {5, 5};
	_padding = {5, 5};
}

/**
 * @brief Destroy the NibblerSFML::NibblerSFML object
 */
NibblerSFML::~NibblerSFML() {
	logInfo("exit SFML");
	_win.close();
}

/**
 * @brief Construct a new NibblerSFML::NibblerSFML object
 *
 * @param src object to copy
 */
NibblerSFML::NibblerSFML(NibblerSFML const &src)
: ANibblerGui() {
	*this = src;
}

// -- Operators ----------------------------------------------------------------

/**
 * @brief Copy this object. (SHOULD NOT be called. Log an error.)
 *
 * @param rhs The object to copy
 * @return NibblerSFML& A reference to the copied object
 */
NibblerSFML &NibblerSFML::operator=(NibblerSFML const &rhs) {
	if (this != &rhs) {
		logErr("unable to copy NibblerSFML");
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
bool NibblerSFML::init(GameInfo &gameInfo) {
	logInfo("loading SFML");

	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;

	int size = std::min(gameInfo.windowSize.x, gameInfo.windowSize.y);

	_win.create(sf::VideoMode(size, size), TITLE, sf::Style::Default, settings);

	this->gameInfo = &gameInfo;

	// Game resizing.
	sf::Vector2u	win_size = _win.getSize();
	sf::Vector2f	game_size = {
		static_cast<float>(this->gameInfo->gameboard.x + 1),
		static_cast<float>(this->gameInfo->gameboard.y + 1)
	};
	sf::Vector2f	block_size = {
		win_size.x / game_size.x,
		win_size.y / game_size.y
	};
	float			block = std::min(block_size.x, block_size.y);
	_block = {std::max(block, 1.f), std::max(block, 1.f)};
	_padding = {std::max(block/2, 1.f), std::max(block/2, 1.f)};

	return true;
}

/**
 * @brief Method to update the input pressed
 */
void NibblerSFML::updateInput() {
	input.direction = Direction::NO_MOVE;
	input.togglePause = false;
	while (_win.pollEvent(_event)) {
		switch (_event.type) {
			// window closed
			case sf::Event::Closed:
				input.quit = true;
				break;
			// window lost focus
			case sf::Event::LostFocus:
				if (gameInfo->play == State::S_PLAY)
					input.togglePause = true;
				break;
			// key pressed
			case sf::Event::KeyPressed:
				if (_inputKeyPressed.find(_event.key.code) != _inputKeyPressed.end())
					_inputKeyPressed[_event.key.code](input);
			default:
				break;
		}
	}
}

/**
 * @brief Draw is called each frame
 *
 * @return true if succeed
 * @return false if failure
 */
bool NibblerSFML::draw() {
	_win.clear();

	sf::View board(sf::FloatRect(0.f, 0.f, GAMESIZE_X, GAMESIZE_Y));

	glm::vec2	ratio;
	ratio.y = 1.f;
	ratio.x = static_cast<float>(_win.getSize().y) / static_cast<float>(_win.getSize().x);
	if (ratio.x > 1.f) {
		ratio.x = 1.f;
		ratio.y = static_cast<float>(_win.getSize().x) / static_cast<float>(_win.getSize().y);
	}
	board.setViewport(sf::FloatRect(0, 0, ratio.x, ratio.y));
	_win.setView(board);

	_printBoard();

	_printLine(0, "Nibbler");
	_printLine(1, "score: " + std::to_string(gameInfo->score));

	_printSnake();
	_printFood();

	if (gameInfo->play == State::S_PAUSE) {
		_printState("PAUSE", sf::Color(0xE6903Aaa));
	}

	if (gameInfo->play == State::S_GAMEOVER) {
		_printState("GAME OVER", sf::Color(0xFC4F4899));
	}

	_win.display();
	return true;
}

// -- Private Methods ----------------------------------------------------------

/**
 * @brief Print the game board
 */
void	NibblerSFML::_printBoard() {
	float		size_board = gameInfo->gameboard.x * gameInfo->gameboard.y;
	sf::Color	color[2] = {
		sf::Color(0x252526FF),		// #252526ff
		sf::Color(0x1E1E1EFF),		// #1E1E1Eff
	};

	sf::RectangleShape rect(sf::Vector2f(_padding.x * 2 + gameInfo->gameboard.x * _block.x,
	_padding.y * 2 + gameInfo->gameboard.y * _block.y));
	rect.setPosition(0, 0);
	rect.setFillColor(sf::Color(0x587C0CFF));
	_win.draw(rect);

	// Board sized optimisation
	if (size_board >  22500) {
		rect.setSize(sf::Vector2f(gameInfo->gameboard.x * _block.x, gameInfo->gameboard.y * _block.y));
		rect.setPosition(_padding.x, _padding.y);
		rect.setFillColor(color[1]);
		_win.draw(rect);
		return;
	}

	rect.setSize(sf::Vector2f(_block.x, _block.y));
	glm::ivec2	pos = {0, 0};
	for (pos.y = 0; pos.y < gameInfo->gameboard.y; pos.y++) {
		for (pos.x = 0; pos.x < gameInfo->gameboard.x; pos.x++) {
			rect.setPosition(MARGED_POS(pos));
			rect.setFillColor(color[(pos.x+pos.y) % 2]);
			_win.draw(rect);
		}
	}
}

/**
 * @brief print the snake
 */
void	NibblerSFML::_printSnake() {
	sf::RectangleShape rect(sf::Vector2f(_block.x, _block.y));

	for (auto it = gameInfo->snake.begin(); it != gameInfo->snake.end(); ++it) {
		rect.setFillColor(sf::Color((it == gameInfo->snake.begin()
			? 0x5eed00B9  // head color
			: 0x00BD63B9)));  // body color
		rect.setPosition(MARGED_POS((*it)));
		_win.draw(rect);
	}
}

/**
 * @brief Print the food
 */
void	NibblerSFML::_printFood() {
	sf::RectangleShape rect(sf::Vector2f(_block.x, _block.y));

	rect.setFillColor(sf::Color(0xCEAF07FF));

	rect.setPosition(MARGED_POS(gameInfo->food));
	_win.draw(rect);
}

/**
 * @brief Print the string
 *
 * @param line_nb The position of the line
 * @param line The string to print
 */
void	NibblerSFML::_printLine(int line_nb, std::string line) {
	float		width = MARGED_X(gameInfo->gameboard);
	sf::Text	text;

	text.setFont(_font);
	text.setCharacterSize(width / 25);
	text.setString(line);
	text.setFillColor(sf::Color(0x55BAE1AA));
	sf::Vector2f text_size = sf::Vector2f(text.getLocalBounds().width, text.getLocalBounds().height);
	text.setPosition(width - text_size.x - width / 40, line_nb * text_size.y * 1.4f + width / 40 + _padding.y);
	_win.draw(text);
}

/**
 * @brief Print a string as a state
 *
 * @param str The string to print
 * @param color The color of the background
 */
void	NibblerSFML::_printState(std::string str, sf::Color color) {
	float		width = GAMESIZE_X;
	float		height = GAMESIZE_Y;
	sf::Text	text;

	text.setFont(_font);
	text.setCharacterSize(width / 10);
	text.setString(str);
	text.setFillColor(sf::Color::Black);
	sf::Vector2f text_size = sf::Vector2f(text.getLocalBounds().width, text.getLocalBounds().height);
	text.setPosition((width / 2) - (text_size.x / 2), (height / 2) - (text_size.y / 2) - text.getLocalBounds().top);
	sf::Vector2f rect_size = sf::Vector2f(text_size.x * 1.5f, text_size.y * 1.5f);
	sf::RectangleShape rect(rect_size);
	rect.setFillColor(color);
	rect.setPosition((width / 2) - (rect_size.x / 2), (height / 2) - (rect_size.y / 2));
	_win.draw(rect);
	_win.draw(text);
}

// -- Exceptions errors --------------------------------------------------------

NibblerSFML::NibblerSFMLException::NibblerSFMLException()
: std::runtime_error("NibblerSFML Exception") {}

NibblerSFML::NibblerSFMLException::NibblerSFMLException(const char* what_arg)
: std::runtime_error(std::string(std::string("NibblerSFMLError: ") + what_arg).c_str()) {}

// -- Library external access functions ----------------------------------------

/**
 * @brief Function of the lib that can be externally called
 */
extern "C" {
	/**
	 * @brief Allow to create a new NibblerSFML object
	 *
	 * @return ANibblerGui* new object created
	 */
	ANibblerGui *makeNibblerSFML() {
		return new NibblerSFML();
	}
}
