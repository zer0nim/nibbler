#ifndef ANIBBLERGUI_HPP_
#define ANIBBLERGUI_HPP_

#define NO_GUI_LOADED 255

#include <unistd.h>
#include <iostream>
#include <deque>

#include <glm/glm.hpp>
#include "glm/gtx/string_cast.hpp"

#define TITLE	"nibbler"
#define WIDTH	800
#define HEIGHT	600

namespace Direction {
	enum eDirection {
		NO_MOVE,
		MOVE_UP,
		MOVE_RIGHT,
		MOVE_DOWN,
		MOVE_LEFT,
	};
}

namespace State {
	enum eState {
		S_PLAY,
		S_PAUSE,
		S_GAMEOVER,
	};
}

struct GameInfo {
	glm::ivec2				gameboard;
	glm::ivec2				food;
	State::eState			play;
	std::deque<glm::ivec2>	snake;

	GameInfo();
	GameInfo(int height, int width);
	~GameInfo();
	GameInfo(GameInfo const &src);
	GameInfo &operator=(GameInfo const &rhs);
};

class ANibblerGui {
	public:
		ANibblerGui();
		virtual ~ANibblerGui();
		ANibblerGui(ANibblerGui const &src);
		ANibblerGui &operator=(ANibblerGui const &rhs);

		virtual	bool	init(GameInfo &gameInfo) = 0;
		virtual void	updateInput() = 0;
		virtual	bool	draw() = 0;

		struct Input {
			bool		quit;

			Direction::eDirection	direction;
			uint8_t		loadGuiID;

			Input();
			Input(Input const &src);
			Input &operator=(Input const &rhs);
		};

		Input input;

	protected:
		GameInfo *gameInfo;
};

typedef ANibblerGui *(*nibblerGuiCreator)();

#endif  // ANIBBLERGUI_HPP_
