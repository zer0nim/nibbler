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

	argsParser.setProgDescr("The purpose of this project is to create our version of the game Snake,\n"\
	"with at least 3 different GUIs. These GUIs being shared libraries.");

	// width
	argsParser.addArgument("width", ArgType::INT64)
		.setHelp("set the windows width")
		.setMinI64(200)
		.setMaxI64(7680)
		.setDefaultI64(1200);

	// --gui -g
	argsParser.addArgument("gui", ArgType::UINT32)
		.setOptional("gui", 'g')
		.setHelp("change the starting gui id")
		.setMaxUI32(2)
		.setDefaultUI32(0);
	// --boardSize -b
	argsParser.addArgument("boardSize", ArgType::UINT32)
		.setOptional("boardSize", 'b')
		.setHelp("set the board size")
		.setDefaultUI32(16);
	// --speed -s
	argsParser.addArgument("speed", ArgType::FLOAT)
		.setOptional("speed", 's')
		.setHelp("change the game speed")
		.setMinF(0.0f)
		.setMaxF(100.0f)
		.setDefaultF(10.5f);

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
