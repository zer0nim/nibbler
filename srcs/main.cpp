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

	argsParser.addArgument("testBool", ArgType::STRING);
	argsParser.addArgument("testString", ArgType::BOOL);
	argsParser.addArgument("testInt32", ArgType::INT32);
	argsParser.addArgument("testInt64", ArgType::INT64);
	argsParser.addArgument("testUint32", ArgType::UINT32);
	argsParser.addArgument("testUint64", ArgType::UINT64);
	argsParser.addArgument("testFloat", ArgType::FLOAT);

	// // width
	// argsParser.addArgument("width", ArgType::UINT32)
	// 	.setHelp("set the windows width")
	// 	.setMinUI32(200)
	// 	.setMaxUI32(7680)
	// 	.setDefaultUI32(1200);

	// // height
	// argsParser.addArgument("height", ArgType::UINT32)
	// 	.setHelp("set the windows height")
	// 	.setMinUI32(200)
	// 	.setMaxUI32(4320)
	// 	.setDefaultUI32(800);

	// // --gui -g
	// argsParser.addArgument("gui", ArgType::UINT32)
	// 	.setOptional("gui", 'g')
	// 	.setHelp("change the starting gui id")
	// 	.setMaxUI32(2)
	// 	.setDefaultUI32(0);

	// // --boardSize -b
	// argsParser.addArgument("boardSize", ArgType::UINT32)
	// 	.setOptional("boardSize", 'b')
	// 	.setHelp("set the board size")
	// 	.setDefaultUI32(16);
	// // --speed -s
	// argsParser.addArgument("speed", ArgType::FLOAT)
	// 	.setOptional("speed", 's')
	// 	.setHelp("change the game speed")
	// 	.setMinF(0.0f)
	// 	.setMaxF(100.0f)
	// 	.setDefaultF(10.5f);

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
