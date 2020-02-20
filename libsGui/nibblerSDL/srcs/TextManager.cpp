#include "TextManager.hpp"
#include "Logging.hpp"

TextManager::TextManager(GameInfo const *gameInfo)
: _gameInfo(gameInfo),
  _textRender(nullptr) {}

TextManager::TextManager()
: _textRender(nullptr) {
}

TextManager::~TextManager() {
	delete _textRender;
}

TextManager::TextManager(TextManager const &src) {
	*this = src;
}

TextManager &TextManager::operator=(TextManager const &rhs) {
	if (this != &rhs) {
		logErr("The copy operator should not be called");
	}
	return *this;
}


bool	TextManager::init() {
	try {
		_textRender = new TextRender(_gameInfo->windowSize.x, _gameInfo->windowSize.y);
		// create normal font
		_normalTxtSize = _gameInfo->windowSize.x / 50;
		_textRender->loadFont("normalTxt", "assets/fonts/snakebold.ttf", _normalTxtSize);
		// create title font
		_titleTxtSize = _gameInfo->windowSize.x / 10;
		_textRender->loadFont("titleTxt", "assets/fonts/snakebold.ttf", _titleTxtSize);
	}
	catch (TextRender::TextRenderError & e) {
        logErr("TextRender: " << e.what());
		return false;
	}

	return true;
}

void	TextManager::draw() {
	_drawScore();

	if (_gameInfo->play == State::S_PAUSE) {
		_drawStatus("PAUSE", NORMAL_TEXT_COLOR);
	}
	else if (_gameInfo->play == State::S_GAMEOVER) {
		_drawStatus("GAME OVER", GAME_OVER_TEXT_COLOR);
	}
}

void	TextManager::_drawScore() {
	int x = TXT_PADDING_TOP;
	int y = _gameInfo->windowSize.y - _normalTxtSize - TXT_PADDING_LEFT;
	int lineSz = _normalTxtSize * 1.2;
	std::string text = "score: " + std::to_string(_gameInfo->snake.size());
	_textRender->write("normalTxt", text, x, y, 1, NORMAL_TEXT_COLOR);
	y -= lineSz;
}

void	TextManager::_drawStatus(std::string const &text, glm::vec3 const color) {
	float x = _gameInfo->windowSize.x / 2 -
		_textRender->strWidth("titleTxt", text) / 2;
	float y = _gameInfo->windowSize.y / 2 - _titleTxtSize / 2;
	_textRender->write("titleTxt", text, x, y, 1, color);
}
