#ifndef ANIBBLERGUI_HPP_
#define ANIBBLERGUI_HPP_

#define NO_GUI_LOADED 255

#define VOID_POS glm::ivec2 {-1, -1}

#include <unistd.h>
#include <iostream>
#include <deque>

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>
#include "glm/gtx/string_cast.hpp"

#define TITLE	"nibbler"
#define WIDTH	800
#define HEIGHT	600

namespace Direction {
	enum Enum {
		NO_MOVE,
		MOVE_UP,
		MOVE_RIGHT,
		MOVE_DOWN,
		MOVE_LEFT,
	};
}

// to use enum as map key: std::map< EnumType, Whatever, EnumClassHash>
struct EnumClassHash {
	template<typename T>
	std::size_t operator()(T t) const {
		return static_cast<std::size_t>(t);
	}
};

namespace State {
	enum Enum {
		S_PLAY,
		S_PAUSE,
		S_GAMEOVER,
	};
}

struct GameInfo {
	glm::ivec2				windowSize;
	glm::ivec2				gameboard;
	glm::ivec2				food;
	State::Enum				play;
	std::deque<glm::ivec2>	snake;
	int						score;
	float					snakeSpeed;
	Direction::Enum			direction;

	GameInfo();
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
			bool			quit;
			bool			togglePause;

			Direction::Enum	direction;
			uint8_t			loadGuiID;

			Input();
			Input(Input const &src);
			Input &operator=(Input const &rhs);
		};

		Input input;

	protected:
		// read only gameInfo updated by gameManager
		GameInfo const *gameInfo;
};

typedef ANibblerGui *(*nibblerGuiCreator)();

#endif  // ANIBBLERGUI_HPP_
