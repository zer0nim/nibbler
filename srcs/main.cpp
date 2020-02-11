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

	// // width
	// argsParser.addArgument("width", ArgType::UINT32)
	// 	.setHelp("set the windows width")
	// 	.setMinU(200)
	// 	.setMaxU(7680)
	// 	.setDefaultU(1200);

	// // height
	// argsParser.addArgument("height", ArgType::UINT32)
	// 	.setHelp("set the windows height")
	// 	.setMinU(200)
	// 	.setMaxU(4320)
	// 	.setDefaultU(800);

	// // --gui -g
	// argsParser.addArgument("gui", ArgType::UINT32)
	// 	.setOptional("gui", 'g')
	// 	.setHelp("change the starting gui id")
	// 	.setMaxU(2)
	// 	.setDefaultU(0);

	// // --boardSize -b
	// argsParser.addArgument("boardSize", ArgType::UINT32)
	// 	.setOptional("boardSize", 'b')
	// 	.setHelp("set the board size")
	// 	.setDefaultU(16);
	// // --speed -s
	// argsParser.addArgument("speed", ArgType::FLOAT)
	// 	.setOptional("speed", 's')
	// 	.setHelp("change the game speed")
	// 	.setMinF(0.0f)
	// 	.setMaxF(100.0f)
	// 	.setDefaultF(10.5f);

	// // TODO(zer0nim): for testing, remove later --------------------------------
	// argsParser.addArgument("verbose", ArgType::BOOL)
	// 	.setOptional('v', "verbose")
	// 	.setStoreTrue();

	// argsParser.addArgument("name", ArgType::STRING)
	// 	.setOptional("name");

	argsParser.addArgument("testString", ArgType::STRING);
	argsParser.addArgument("testBool", ArgType::BOOL);
	argsParser.addArgument("testInt8", ArgType::INT8);
	argsParser.addArgument("testInt16", ArgType::INT16);
	argsParser.addArgument("testInt32", ArgType::INT32);
	argsParser.addArgument("testInt64", ArgType::INT64);
	argsParser.addArgument("testUint8", ArgType::UINT8);
	argsParser.addArgument("testUint16", ArgType::UINT16);
	argsParser.addArgument("testUint32", ArgType::UINT32);
	argsParser.addArgument("testUint64", ArgType::UINT64);
	argsParser.addArgument("testFloat", ArgType::FLOAT);
	argsParser.addArgument("testDouble", ArgType::DOUBLE);
	argsParser.addArgument("testLDouble", ArgType::L_DOUBLE);

	try {
		argsParser.parseArgs();
	}
	catch(ArgsParser::ArgsParserUsage const &e) {
		return EXIT_SUCCESS;
	}
	catch(ArgsParser::ArgsParserException const &e) {
		return EXIT_FAILURE;
	}

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
