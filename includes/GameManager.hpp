#ifndef GAMEMANAGER_HPP_
#define GAMEMANAGER_HPP_

#define GLM_ENABLE_EXPERIMENTAL

#ifndef DEBUG
	#define DEBUG false
#endif
#define DEBUG_FPS_LOW	DEBUG & true
#define FPS 10

#define V_UP glm::ivec2(0, -1)
#define V_RIGHT glm::ivec2(1, 0)
#define V_DOWN glm::ivec2(0, 1)
#define V_LEFT glm::ivec2(-1, 0)

#include <iostream>
#include <stdexcept>
#include <deque>
#include <chrono>

#include <glm/glm.hpp>
#include "glm/gtx/string_cast.hpp"

#include "Logging.hpp"
#include "DynGuiManager.hpp"
#include "ANibblerGui.hpp"

namespace State {
	enum eState {
		S_PLAY,
		S_PAUSE,
		S_GAMEOVER,
	};
}

class GameManager {
private:
	// Members
	glm::ivec2				_gameboard;
	glm::ivec2				_food;
	State::eState			_play;
	std::deque<glm::ivec2>*	_body;
	float					_moveSpeed;
	Direction::eDirection	_direction;
	int						_eating;

	// Methods
	bool					_move(Direction::eDirection dir);
	std::chrono::milliseconds _getMs();
	Direction::eDirection	_acceptedDirection(Direction::eDirection dir);
	bool					_isEmpty(glm::ivec2 pos) const;
	void					_generateFood();
	bool					_checkContact();

public:
	// Members
	DynGuiManager	dynGuiManager;

	// Constructors
	GameManager();
	explicit GameManager(int height, int width, float moveSpeed);
	~GameManager();
	GameManager(GameManager const &src);

	// Operators
	GameManager&			operator=(GameManager const &rhs);
	friend std::ostream&	operator<<(std::ostream& os, const GameManager& my_class);

	// Accessors
	std::string				toString() const;
	std::string				getBoard() const;
	std::deque<glm::ivec2>*	getBody() const;
	glm::ivec2				getHead() const;

	// Methods
	bool					init();
	void					run();
	void					restart();

	// Exceptions
	class GameManagerException : public std::runtime_error {
	public:
		GameManagerException();
		explicit GameManagerException(const char* what_arg);
	};
};

#endif  // GAMEMANAGER_HPP_
