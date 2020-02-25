#pragma once

#include <curses.h>
#include <iostream>
#include <map>
#include <vector>
#include "ANibblerGui.hpp"
#include "Window.hpp"
#include "BorderWindow.hpp"

class NibblerNcurses : public ANibblerGui {
	public:
		NibblerNcurses();
		virtual ~NibblerNcurses();
		NibblerNcurses(NibblerNcurses const &src);
		NibblerNcurses &operator=(NibblerNcurses const &rhs);

		// Methods
		virtual bool	init(GameInfo &gameInfo);
		virtual void	updateInput();
		virtual bool	draw();

		static void		resizeHandler(int sig);

		// Exceptions
		class NibblerNcursesException : public std::runtime_error {
		public:
			NibblerNcursesException();
			explicit NibblerNcursesException(const char* what_arg);
		};

	private:
		// Members
		typedef void(*inputFuncPtr)(Input &);
		static	std::map<int , inputFuncPtr>	_inputKeyPressed;

		typedef std::vector<Window *> stack_type;
		stack_type				_stack;
		glm::ivec2				_win;
		glm::ivec2				_tail;
		State::Enum				_state;

		// Methods
		std::string		_center(std::string input, int width);
		void			_touchAll();
		void			_drawAll();
};
