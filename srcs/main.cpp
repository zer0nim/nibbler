#include <dlfcn.h>
#include <iostream>

#include "nibbler.hpp"
#include "Logging.hpp"
#include "DynGuiManager.hpp"
#include "ArgsParser.hpp"

int main(int ac, char * const *av) {
	// uint8_t			guiId = 0;
	DynGuiManager	dynGuiManager;

	initLogs();  // init logs functions

	// process args ------------------------------------------------------------
	ArgsParser	argsParser(ac, av);

	// width
	argsParser.addArgument("width", ArgType::INT)
		.setHelp("set the windows width")
		.setMinI(200)
		.setMaxI(7680)
		.setDefaultI(600);

	// --gui -g
	argsParser.addArgument("gui", ArgType::INT)
		.setOptional("gui", 'g')
		.setHelp("change the starting gui id")
		.setDefaultI(0);
	// --speed -s
	argsParser.addArgument("speed", ArgType::FLOAT)
		.setOptional("speed", 's')
		.setHelp("change the game speed")
		.setMinF(0.0f)
		.setMaxF(100.0f)
		.setDefaultF(10.0f);
	// --boardSize -b
	argsParser.addArgument("boardSize", ArgType::INT)
		.setOptional("boardSize", 'b')
		.setHelp("set the board size")
		.setDefaultI(16);
	// --verbose
	argsParser.addArgument("verbose", ArgType::BOOL)
		.setOptional("verbose")
		.setHelp("activate verbose mode")
		.setStoreTrue(true);

	argsParser.init();

	argsParser.parseArgs();

	// run the game ------------------------------------------------------------
	// // load the defaut gui
	// try {
	// 	dynGuiManager.loadGui(guiId);
	// 	dynGuiManager.nibblerGui->init();

	// 	gameLoop(dynGuiManager);
	// }
	// catch(const std::exception& e) {
	// 	logErr(e.what());
	// 	return EXIT_FAILURE;
	// }

	return EXIT_SUCCESS;
}
