#pragma once

#include <curses.h>
#include <iostream>
#include "ANibblerGui.hpp"

class NibblerNcurses : public ANibblerGui {
	public:
		NibblerNcurses();
		virtual ~NibblerNcurses();
		NibblerNcurses(NibblerNcurses const &src);
		NibblerNcurses &operator=(NibblerNcurses const &rhs);

		virtual bool	init(GameInfo &gameInfo);
		virtual void	updateInput();
		virtual bool	draw();

	private:
		WINDOW *		_win;
		std::string _toString() const;
		std::string _getBoard() const;
};
