#include <dlfcn.h>
#include <iostream>

#include "nibbler.hpp"
#include "Logging.hpp"
#include "GameManager.hpp"
#include "ArgsParser.hpp"

int main(int ac, char * const *av) {
	GameManager		game = GameManager(25, 25, 3);
	(void)ac;
	(void)av;

	initLogs();  // init logs functions

	// run the game ------------------------------------------------------------
	// load the defaut gui
	if (!game.init())
		return EXIT_FAILURE;
	try {
		game.run();
	}
	catch(const std::exception& e) {
		logErr(e.what());
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}
