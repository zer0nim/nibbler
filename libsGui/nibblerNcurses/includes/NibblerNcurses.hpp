#pragma once

#include <curses.h>
#include <iostream>
#include <map>
#include <vector>
#include "ANibblerGui.hpp"
#include "IWindow.hpp"
#include "Window.hpp"

/**
 * @brief NibblerNcurses object
 */
class NibblerNcurses : public ANibblerGui {
	public:
		// Members
		bool			drawable;  ///< Says if the game can be drew

		// Constructors
		NibblerNcurses();
		virtual ~NibblerNcurses();
		NibblerNcurses(NibblerNcurses const &src);
		NibblerNcurses &operator=(NibblerNcurses const &rhs);

		// Methods
		virtual bool	init(GameInfo &gameInfo);
		virtual void	updateInput();
		virtual bool	draw();
		void			resize();

		// Exceptions
		class NibblerNcursesException : public std::runtime_error {
		public:
			NibblerNcursesException();
			explicit NibblerNcursesException(const char* what_arg);
		};

	private:
		// Members
		typedef void(*inputFuncPtr)(Input &, NibblerNcurses &);
		static	std::map<int , inputFuncPtr>	_inputKeyPressed;  ///< map of key pressed

		IWindow					*_win;  ///< window object
		glm::ivec2				_win_size;  ///< window size
		glm::ivec2				_tail;  ///< position of the tail of the snake
		State::Enum				_state;  ///< state of the game

		// Methods
		std::string		_center(std::string input, int width);
		void			_touchAll();
		void			_drawAll();
};
