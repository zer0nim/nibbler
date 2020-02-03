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

	// --width -w
	argsParser.addArgument(ArgType::INT)
		.setShortName("w")
		.setLongName("width")
		.setHelp("set the windows width")
		.setMinI(200)
		.setMaxI(7680)
		.setDefaultI(600)
		.isRequired(true);
	// --gui -g
	argsParser.addArgument(ArgType::INT)
		.setShortName("g")
		.setLongName("gui")
		.setHelp("change the starting gui id");
	// --speed -s
	argsParser.addArgument(ArgType::FLOAT)
		.setShortName("s")
		.setLongName("speed")
		.setHelp("change the game speed")
		.setMinF(0.0f)
		.setMaxF(100.0f)
		.setDefaultF(10.0f)
		.isRequired(true);
	// --boardSize -b
	argsParser.addArgument(ArgType::INT)
		.setShortName("b")
		.setLongName("boardSize")
		.setHelp("set the board size")
		.setDefaultI(true);
	// --speed -s
	argsParser.addArgument(ArgType::BOOL)
		.setShortName("v")
		.setLongName("verbose")
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
