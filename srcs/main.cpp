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

	ArgsParser	argsParser;
	argsParser.init();

	std::cout << argsParser.addArgument()
		.setShortName("n")
		.setLongName("name")
		.setHelp("set your name")
		.isRequired(true)
		.setDefaultS("billy")
		.setMinI(2)
		.setMaxI(22)
	<< std::endl;

	std::cout << argsParser.addArgument(ArgType::STRING)
		.setShortName("n")
		.setLongName("name")
		.setHelp("set your name")
		.isRequired(true)
	<< std::endl;

	std::cout << argsParser.addArgument(ArgType::BOOL)
		.setShortName("v")
		.setLongName("verbose")
		.setHelp("display usage of the program")
		.isRequired(true)
		.setStoreTrue()
		.setDefaultB(true)
	<< std::endl;

	std::cout << argsParser.addArgument(ArgType::INT)
		.setShortName("w")
		.setLongName("width")
		.setHelp("set windows width")
		.isRequired(true)
		.setMinI(33)
		.setMaxI(43)
		.setDefaultI(42)
	<< std::endl;

	std::cout << argsParser.addArgument(ArgType::FLOAT)
		.setShortName("s")
		.setLongName("speed")
		.setHelp("set move speed")
		.isRequired(true)
		.setDefaultF(12.5)
		.setMinF(-42.3)
		.setMaxF(103)
	<< std::endl;

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
