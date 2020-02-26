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

Input::Input()
: quit(false), direction(Direction::MOVE_UP), loadGuiID(NO_GUI_LOADED) {
}

Input::Input(Input const &src) {
	*this = src;
}

Input &Input::operator=(Input const &rhs) {
	if (this != &rhs) {
		direction = rhs.direction;
		loadGuiID = rhs.loadGuiID;
	}
	return *this;
}

// -- GameInfo -----------------------------------------------------------------

GameInfo::GameInfo() {
	windowSize = {1200, 800};
	gameboard = {1200, 800};
	food = VOID_POS;
	play = State::S_PAUSE;
}
