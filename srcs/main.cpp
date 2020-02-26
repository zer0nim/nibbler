#include <dlfcn.h>
#include <iostream>
#include <iomanip>

#include "nibbler.hpp"
#include "Logging.hpp"
#include "GameManager.hpp"
#include "ArgsParser.hpp"

bool	manageArgs(ArgsParser &ap, uint8_t &gui, GameInfo &gameInfo, LAN_MODE::Enum &lanMode) {
	// -- process arguments ----------------------------------------------------
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
	ap.addArgument("gameboard", ArgType::UINT32, 'b', "gameboard")
		.setHelp("set the gameboard size")
		.setDefaultU(16)
		.setMinU(10)
		.setMaxU(1000);
	// -s --speed
	ap.addArgument("snakeSpeed", ArgType::FLOAT, 's', "snakeSpeed")
		.setHelp("change the snake speed")
		.setMinF(0.0f)
		.setMaxF(100.0f)
		.setDefaultF(10.5f);
	// --host-game
	ap.addArgument("host-game", ArgType::BOOL, "host-game")
		.setHelp("host a lan game")
		.setStoreTrue();
	// --join-game
	ap.addArgument("join-game", ArgType::BOOL, "join-game")
		.setHelp("join a lan game")
		.setStoreTrue();

	// -- run the parser -------------------------------------------------------
	try {
		ap.parseArgs();
	}
	catch(ArgsParser::ArgsParserUsage const &e) {
		return false;
	}
	catch(const std::exception& e) {
		logErr(e.what());
		return false;
	}

	// -- retrieve values ------------------------------------------------------
	// gui
	gui = ap.get<uint8_t>("gui");
	// windowSize
	gameInfo.windowSize = {ap.get<uint32_t>("width"), ap.get<uint32_t>("height")};
	// gameboard
	gameInfo.gameboard.x = ap.get<uint32_t>("gameboard");
	gameInfo.gameboard.y = gameInfo.gameboard.x;
	// snakeSpeed
	gameInfo.snakeSpeed = ap.get<float>("snakeSpeed");
	// host-game, join-game
	lanMode = LAN_MODE::SOLO;
	if (ap.get<bool>("host-game")) {
		lanMode = LAN_MODE::HOST;
	}
	else if (ap.get<bool>("join-game")) {
		lanMode = LAN_MODE::CLIENT;
	}

	logDebug("-- gameInfo ------------");
	logDebug(" windowSize: " << glm::to_string(gameInfo.windowSize));
	logDebug(" gameboard: " << glm::to_string(gameInfo.gameboard));
	logDebug(" play: " << gameInfo.play);
	logDebug(" snakeSpeed: " << gameInfo.snakeSpeed);
	logDebug("-----------------------");
	return true;
}

int	main(int ac, char * const *av) {
	ArgsParser		ap(ac, av);
	uint8_t			gui = 0;
	GameInfo		gameInfo;
	LAN_MODE::Enum	lanMode;
	GameManager		game(gameInfo);

	initLogs();  // init logs functions context, Err/Warn/Info...

	// parse arguments
	if (!manageArgs(ap, gui, gameInfo, lanMode)) {
		return EXIT_FAILURE;
	}
	std::cout << std::endl;

	// run the game
	try {
		// init gameManager
		if (!game.init(gui, lanMode)) {
			return EXIT_FAILURE;
		}
		logInfo("let's run the game");
		// run the game
		game.run();
	}
	catch(const std::exception& e) {
		logErr(e.what());
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}
