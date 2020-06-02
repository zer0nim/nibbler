#include <dlfcn.h>
#include <iostream>
#include <iomanip>

#include "nibbler.hpp"
#include "Logging.hpp"
#include "GameManager.hpp"
#include "ArgsParser.hpp"
#include "GameInfo.pb.hpp"
#include "Input.pb.hpp"

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
		.setMaxU(NB_GUI - 1)
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
	logDebug("-----------------------\n");
	return true;
}

void	testProtoBuf() {
	GOOGLE_PROTOBUF_VERIFY_VERSION;

	logDebug("test Protobuf");

	// -- create and fill protobuf GameInfo ------------------------------------
	logDebug("create and fill protobuf GameInfo");
	gameInfoProto::GameInfo	gameInfo;
	// set food
	gameInfo.mutable_food()->set_x(42);
	gameInfo.mutable_food()->set_y(23);
	// set play
	gameInfo.set_play(gameInfoProto::State::S_PAUSE);
	// set snake
	auto body = gameInfo.mutable_snake()->mutable_body();
	uint32_t	i = 0;
	for (gameInfoProto::IVec2 &pos : *body) {
		pos.set_x(i);
		pos.set_y(i + 10);
		++i;
	}
	// set snakeSpeed
	gameInfo.set_snakespeed(5.6);
	// set direction
	gameInfo.set_direction(gameInfoProto::Direction::MOVE_LEFT);

	// -- serialize it to serGameInfo ------------------------------------------
	logDebug("serialize it to serGameInfo");
	std::string const serGameInfo = gameInfo.SerializeAsString();

	// -- try to deserialize and retrieve values -------------------------------
	logDebug("try to deserialize and retrieve values");
	gameInfoProto::GameInfo	desGameInfo;
	desGameInfo.ParseFromString(serGameInfo);
	logDebug("food: {" << desGameInfo.food().x() << ", " << desGameInfo.food().y() << "}");
	logDebug("snakespeed: " << desGameInfo.snakespeed());
	logDebug("...");

	// -- test protobuf Input --------------------------------------------------
	inputProto::Input	input;
	input.set_direction(inputProto::Direction::MOVE_LEFT);
	input.set_togglepause(true);
	input.set_loadguiid(2);
	logDebug("input guiid: " << input.loadguiid());
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

	// testProtoBuf();

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
