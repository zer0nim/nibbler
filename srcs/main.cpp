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
	argsParser.addArgument("width", ArgType::INT64)
		.setHelp("set the windows width")
		.setMinI64(200)
		.setMaxI64(7680)
		.setDefaultI64(600);


	argsParser.addArgument("test", ArgType::STRING)
		.setOptional("test", 't')
		.setHelp("test string")
		.setMinLength(3)
		.setMaxLength(22)
		.setDefaultS("Hey !");
	// --hey
	argsParser.addArgument("hey", ArgType::BOOL)
		.setOptional("hey", 'h')
		.setHelp("test hey");
	// --verbose
	argsParser.addArgument("verbose", ArgType::BOOL)
		.setOptional("verbose")
		.setHelp("activate verbose mode")
		.setStoreTrue(true);

	// --gui -g
	argsParser.addArgument("gui", ArgType::INT32)
		.setOptional("gui", 'g')
		.setHelp("change the starting gui id")
		.setMinI32(0)
		.setMaxI32(2)
		.setDefaultI32(0);
	// --boardSize -b
	argsParser.addArgument("boardSize", ArgType::INT32)
		.setOptional("boardSize", 'b')
		.setHelp("set the board size")
		.setDefaultI32(16);
	// --speed -s
	argsParser.addArgument("speed", ArgType::FLOAT)
		.setOptional("speed", 's')
		.setHelp("change the game speed")
		.setMinF(0.0f)
		.setMaxF(100.0f)
		.setDefaultF(10.0f);

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
