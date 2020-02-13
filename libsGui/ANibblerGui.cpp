#include "ANibblerGui.hpp"

ANibblerGui::ANibblerGui() {
	gameInfo = nullptr;
}

ANibblerGui::~ANibblerGui() {
}

ANibblerGui::ANibblerGui(ANibblerGui const &src) {
	*this = src;
}

ANibblerGui &ANibblerGui::operator=(ANibblerGui const &rhs) {
	if (this != &rhs) {
		input = rhs.input;
	}
	return *this;
}

// -- Input --------------------------------------------------------------------

ANibblerGui::Input::Input()
: quit(false), direction(Direction::MOVE_UP), loadGuiID(NO_GUI_LOADED) {
}

ANibblerGui::Input::Input(ANibblerGui::Input const &src) {
	*this = src;
}

ANibblerGui::Input &ANibblerGui::Input::operator=(ANibblerGui::Input const &rhs) {
	if (this != &rhs) {
		direction = rhs.direction;
		loadGuiID = rhs.loadGuiID;
	}
	return *this;
}

// -- GameInfo -----------------------------------------------------------------

GameInfo::GameInfo() {
	snake = std::deque<glm::ivec2>();
	food = {-1, -1};
	play = State::S_PAUSE;
	gameboard = glm::ivec2(25, 25);
}

GameInfo::GameInfo(int height, int width) {
	snake = std::deque<glm::ivec2>();
	food = {-1, -1};
	play = State::S_PAUSE;
	gameboard = glm::ivec2(width, height);
}

GameInfo::GameInfo(GameInfo const &src) {
	*this = src;
}

GameInfo &GameInfo::operator=(GameInfo const &rhs) {
	if (this != &rhs) {
		gameboard = rhs.gameboard;
		food = rhs.food;
		play = rhs.play;
		snake = rhs.snake;
	}
	return *this;
}

GameInfo::~GameInfo() {
}
