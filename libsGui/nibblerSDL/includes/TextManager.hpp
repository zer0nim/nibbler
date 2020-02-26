#ifndef TEXTMANAGER_HPP_
#define TEXTMANAGER_HPP_

#define NORMAL_TEXT_COLOR glm::vec3(0.89f, 0.95f, 1.0f)
#define GAME_OVER_TEXT_COLOR glm::vec3(0.89f, 0.04f, 0.01f)
#define TXT_PADDING_TOP 10
#define TXT_PADDING_LEFT 20

#include "ANibblerGui.hpp"
#include "TextRender.hpp"

class TextManager {
	public:
		explicit TextManager(GameInfo const *gameInfo);
		virtual ~TextManager();
		TextManager(TextManager const &src);
		TextManager &operator=(TextManager const &rhs);

		bool	init();
		void	draw();

	private:
		TextManager();
		void	_drawScore();
		void	_drawStatus(std::string const &text, glm::vec3 const color);

		GameInfo const *_gameInfo;
		TextRender	*_textRender;
		float		_normalTxtSize;
		float		_titleTxtSize;
};

#endif  // TEXTMANAGER_HPP_
