#include <dlfcn.h>
#include <iostream>
#include <iomanip>

#include "nibbler.hpp"
#include "Logging.hpp"
#include "DynGuiManager.hpp"
#include "ArgsParser.hpp"

int	main(int ac, char * const *av) {
	uint8_t			gui = 0;
	DynGuiManager	dynGuiManager;
	ArgsParser		ap(ac, av);

	struct GameInfo {
		uint32_t	width;
		uint32_t	height;
		uint32_t	boardSize;
		uint32_t	speed;
	};
	 GameInfo	gameInfo;


	initLogs();  // init logs functions context, Err/Warn/Info...

	// process arguments ----------------------------------------------------
	ap.setProgDescr("The purpose of this project is to create our version of the game Snake,\n"\
	"with at least 3 different GUIs. These GUIs being shared libraries.");

	// -- positionals args -----------------------------------------------------
	// width
	ap.addArgument("width", ArgType::UINT32)
		.setHelp("set the windows width")
		.setMinU(200)
		.setMaxU(7680);
	// height
	ap.addArgument("height", ArgType::UINT32)
		.setHelp("set the windows height")
		.setMinU(200)
		.setMaxU(4320);

	// -- optionals args -------------------------------------------------------
	// -g --gui
	ap.addArgument("gui", ArgType::UINT8, 'g', "gui")
		.setHelp("change the starting gui id")
		.setMaxU(1)
		.setDefaultU(0);
	// -b --boardSize
	ap.addArgument("boardSize", ArgType::UINT32, 'b', "boardSize")
		.setHelp("set the board size")
		.setDefaultU(16);
	// -s --speed
	ap.addArgument("speed", ArgType::FLOAT, 's', "speed")
		.setHelp("change the game speed")
		.setMinF(0.0f)
		.setMaxF(100.0f)
		.setDefaultF(10.5f);

	// -- run the parser -------------------------------------------------------
	try {
		ap.parseArgs();
	}
	catch(ArgsParser::ArgsParserUsage const &e) {
		return EXIT_SUCCESS;
	}
	catch(ArgsParser::ArgsParserException const &e) {
		return EXIT_FAILURE;
	}

	// ---- retrieve values ----------------------------------------------------
	gameInfo.width = ap.get<uint32_t>("width");
	gameInfo.height = ap.get<uint32_t>("height");
	gui = ap.get<uint8_t>("gui");
	gameInfo.boardSize = ap.get<uint32_t>("boardSize");
	gameInfo.speed = ap.get<float>("speed");

	std::cout << "-- args ------------" << std::endl;
	std::cout << "width:\t\t" << gameInfo.width << std::endl;
	std::cout << "height:\t\t" << gameInfo.height << std::endl;
	std::cout << "gui:\t\t" << +gui << std::endl;
	std::cout << "boardSize:\t" << gameInfo.boardSize << std::endl;
	std::cout << "speed:\t\t" << gameInfo.speed << std::endl;
	std::cout << "--------------------" << std::endl;

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
