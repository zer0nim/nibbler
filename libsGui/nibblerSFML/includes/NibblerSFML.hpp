#pragma once

#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "ANibblerGui.hpp"

#define WIDTH 800
#define HEIGHT 600

class NibblerSFML : public ANibblerGui {
	public:
		NibblerSFML();
		virtual ~NibblerSFML();
		NibblerSFML(NibblerSFML const &src);
		NibblerSFML &operator=(NibblerSFML const &rhs);

		virtual bool	init(GameInfo &gameInfo);
		virtual void	updateInput();
		virtual bool	draw();

	private:
		int		_h_block;
		int		_w_block;
		int		_h_margin;
		int		_w_margin;


		sf::RenderWindow	_win;
		sf::Event			_event;
		std::string			_toString() const;
		std::string			_getBoard() const;
		void				_printBoard();
		void				_printSnake();
		void				_printFood();
};
