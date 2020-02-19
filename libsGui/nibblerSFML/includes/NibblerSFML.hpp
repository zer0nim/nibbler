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
		static	std::map<sf::Keyboard::Key , inputFuncPtr>	_inputKeyPressed;
		sf::RenderWindow	_win;
		sf::Event			_event;
		sf::Font			_font;
		glm::ivec2			_block;
		glm::ivec2			_margin;
		glm::ivec2			_padding;
		bool				_isMoving;
		sf::Vector2i		_relativePos;
		bool				_isActive;

		// Methods
		void				_printBoard();
		void				_printSnake();
		void				_printFood();
		void				_printLine(int line_nb, std::string line);
		void				_printState(std::string str, sf::Color color);
};
