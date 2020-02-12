#include <dlfcn.h>
#include <iostream>
#include <iomanip>

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

	// test to retrive the value
	std::cout << std::boolalpha << std::fixed << std::setprecision(2);
	std::string	testString = argsParser.get<std::string>("testString");
	std::cout << "testString: " << testString << std::endl;
	bool testBool = argsParser.get<bool>("testBool");
	std::cout << "testBool: " << testBool << std::endl;
	int8_t testInt8 = argsParser.get<int8_t>("testInt8");
	std::cout << "testInt8: " << +testInt8 << std::endl;
	int16_t testInt16 = argsParser.get<int16_t>("testInt16");
	std::cout << "testInt16: " << testInt16 << std::endl;
	int32_t testInt32 = argsParser.get<int32_t>("testInt32");
	std::cout << "testInt32: " << testInt32 << std::endl;
	int64_t testInt64 = argsParser.get<int64_t>("testInt64");
	std::cout << "testInt64: " << testInt64 << std::endl;
	uint8_t testUint8 = argsParser.get<uint8_t>("testUint8");
	std::cout << "testUint8: " << +testUint8 << std::endl;
	uint16_t testUint16 = argsParser.get<uint16_t>("testUint16");
	std::cout << "testUint16: " << testUint16 << std::endl;
	uint32_t testUint32 = argsParser.get<uint32_t>("testUint32");
	std::cout << "testUint32: " << testUint32 << std::endl;
	uint64_t testUint64 = argsParser.get<uint64_t>("testUint64");
	std::cout << "testUint64: " << testUint64 << std::endl;
	float_t testFloat = argsParser.get<float_t>("testFloat");
	std::cout << "testFloat: " << testFloat << std::endl;
	double testDouble = argsParser.get<double>("testDouble");
	std::cout << "testDouble: " << testDouble << std::endl;
	long double testLDouble = argsParser.get<long double>("testLDouble");
	std::cout << "testLDouble: " << testLDouble << std::endl;

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
