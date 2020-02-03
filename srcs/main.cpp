#include <dlfcn.h>
#include <iostream>

#include "nibbler.hpp"
#include "Logging.hpp"
#include "DynGuiManager.hpp"
#include "ArgsParser.hpp"

int main(int ac, char * const *av) {
	uint8_t			guiId = 0;
	DynGuiManager	dynGuiManager;

	initLogs();  // init logs functions


// ls: illegal option -- z

	ArgsParser	argsParser;
	argsParser.init();
	std::cout << "default: " << argsParser.addArgument() << std::endl;
	std::cout << "string: " << argsParser.addArgument(ArgType::STRING) << std::endl;
	std::cout << "bool: " << argsParser.addArgument(ArgType::BOOL) << std::endl;
	std::cout << "int: " << argsParser.addArgument(ArgType::INT) << std::endl;
	std::cout << "float: " << argsParser.addArgument(ArgType::FLOAT) << std::endl;
	// argsParser.parseArgs(ac, av);

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
