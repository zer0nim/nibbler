#pragma once

#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "ANibblerGui.hpp"

#define MARGED_X(pos) _padding.x + _block.x * pos.x
#define MARGED_Y(pos) _padding.y + _block.y * pos.y
#define GAMESIZE_X _padding.x * 2 + _block.x * gameInfo->gameboard.x
#define GAMESIZE_Y _padding.y * 2 + _block.y * gameInfo->gameboard.y
#define MARGED_POS(pos) MARGED_X(pos), MARGED_Y(pos)

/**
 * @brief NibblerSFML object
 */
class NibblerSFML : public ANibblerGui {
	public:
		// Constructors
		NibblerSFML();
		virtual ~NibblerSFML();
		NibblerSFML(NibblerSFML const &src);
		// Operators
		NibblerSFML &operator=(NibblerSFML const &rhs);

		// Methods
		virtual bool	init(GameInfo &gameInfo);
		virtual void	updateInput();
		virtual bool	draw();

		// Exceptions
		class NibblerSFMLException : public std::runtime_error {
		public:
			NibblerSFMLException();
			explicit NibblerSFMLException(const char* what_arg);
		};

	private:
		// Members
		typedef void(*inputFuncPtr)(Input &);
		static	std::map<sf::Keyboard::Key , inputFuncPtr>	_inputKeyPressed;  ///< map of key pressed
		sf::RenderWindow	_win;  ///< window object
		sf::Event			_event;  ///< SFML event
		sf::Font			_font;  ///< font used
		glm::ivec2			_block;  ///< block size
		glm::ivec2			_margin;  ///< margin of the game
		glm::ivec2			_padding;  ///< padding of the game (border size)

		// Methods
		void				_printBoard();
		void				_printSnake();
		void				_printFood();
		void				_printLine(int line_nb, std::string line);
		void				_printState(std::string str, sf::Color color);
};
