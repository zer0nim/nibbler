#include "ArgsParser.hpp"

#include <algorithm>
#include <utility>
#include <iomanip>

#include "Logging.hpp"

ArgsParser::ArgsParser() {
}

ArgsParser::ArgsParser(int ac, char * const *av)
: _ac(ac),
  _av(av) {
}

ArgsParser::~ArgsParser() {
	// free _argsInfos vector
	for (auto &&argInfos : _argsInfos) {
		delete argInfos;
	}
	_argsInfos.clear();
}

ArgsParser::ArgsParser(ArgsParser const &src) {
	*this = src;
}

ArgsParser &ArgsParser::operator=(ArgsParser const &rhs) {
	if (this != &rhs) {
		_opts = rhs._opts;
		_longOpts = rhs._longOpts;
		_argsInfos = rhs._argsInfos;
	}
	return *this;
}

void	ArgsParser::usage() const {
	std::cout << "usage: " << _av[0];
	// print arguments list
	for (auto &&argInfos : _argsInfos) {
		// print positional arguments
		if (argInfos->getRequired()) {
			std::cout << " " COLOR_ULINE << argInfos->getName() << COLOR_EOC;
		}
		// print optional arguments
		if (!argInfos->getRequired()) {
			if (argInfos->getShortName() == A_NO_NAME) {
				std::cout << " [" COLOR_BOLD "--" << argInfos->getLongName() << COLOR_EOC;
			}
			else {
				std::cout << " [" COLOR_BOLD "-" << argInfos->getShortName() << COLOR_EOC;
			}

			if (argInfos->needArgument()) {
				std::cout << " " COLOR_ULINE << argInfos->getName() << COLOR_ULINE_R;
			}

			std::cout << "]";
		}
	}

	uint32_t	nbPositional = std::count_if(std::begin(_argsInfos), std::end(_argsInfos),
		[] (AInfoArg * const argInfos) {
			return argInfos->getRequired(); });

	// print positional args help
	if (nbPositional > 0) {
		std::cout << COLOR_ULINE "\n\npositional arguments" COLOR_ULINE_R;
		for (auto &&argInfos : _argsInfos) {
			if (argInfos->getRequired()) {
				std::cout << "\n  " COLOR_ULINE << argInfos->getName() << COLOR_EOC ":  " << \
				argInfos->getHelp() << std::endl;
				std::cout << "  " << *argInfos << std::endl;
			}
		}
	}

	// print optional args help
	if (_argsInfos.size() - nbPositional > 0) {
		std::cout << (nbPositional > 0 ? "\n" : "\n\n");
		std::cout << COLOR_ULINE "optional arguments" COLOR_ULINE_R;
		for (auto &&argInfos : _argsInfos) {
			if (!argInfos->getRequired()) {
				std::cout << "\n  " COLOR_ULINE << argInfos->getName() << COLOR_EOC ":  ";

				// if the short name is available
				if (argInfos->getShortName() != A_NO_NAME) {
					std::cout << COLOR_BOLD "-" << argInfos->getShortName() << COLOR_EOC;
					if (!argInfos->getLongName().empty()) {
						std::cout << ", ";
					}
				}
				if (!argInfos->getLongName().empty()) {
					std::cout << COLOR_BOLD "--" << argInfos->getLongName() << COLOR_EOC;
				}
				std::cout << "  " << argInfos->getHelp() << "\n  " << *argInfos << std::endl;
			}
		}
	}

	// print program description
	if (!_progDescr.empty()) {
		std::cout << (nbPositional > 0 || _argsInfos.size() - nbPositional > 0 \
		? "\n" : "\n\n");
		std::cout << COLOR_ULINE "description" COLOR_ULINE_R << std::endl;
		std::cout << _progDescr << std::endl;
	}
}

bool	ArgsParser::checkOptsAvailability(std::string const &longName, char shortName) {
	// The -W option is reserved by POSIX.2 for implementation extensions
	if (shortName == 'W') {
		logErr("the -W option is reserved by POSIX.2 for implementation extensions");
		return EXIT_FAILURE;
	}

	// refuse char '-' at the begining of a long/short name
	if (shortName == '-' || longName[0] == '-') {
		logErr("you can't put char '-' at the begining of a long/short name");
		return EXIT_FAILURE;
	}

	// refuse empty longName && empty shortName
	if (longName.empty() && shortName == A_NO_NAME) {
		logErr("you need to specify at least a shortName or a longName");
		return EXIT_FAILURE;
	}

	// check shortName/longName duplicates
	uint32_t	nbDuplicates = std::count_if(std::begin(_argsInfos), std::end(_argsInfos),
		[longName, shortName] (AInfoArg * const argInfos) {
			return (argInfos->getShortName() != A_NO_NAME && shortName != A_NO_NAME && \
				argInfos->getShortName() == shortName) || (!argInfos->getLongName().empty() && argInfos->getLongName() == longName);
		});
	if (nbDuplicates > 0) {
		logErr("duplicate optional arg name: " << "-" << shortName << ", --" << longName);
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}

// create new arg of the specified type, add it to _argsInfos, then return a ref
AInfoArg	&ArgsParser::addArgument(std::string name, ArgType::Enum type) {
	AInfoArg	*newElem = nullptr;

	// refuse empty name
	if (name.empty()) {
		logErr("addArgument don't accept empty name !");
		throw ArgsParserException();
	}

	// create new argument
	switch (type) {
		case ArgType::BOOL:
			newElem = new BoolArg(this, name);
			break;
		case ArgType::INT32:
			newElem = new Int32Arg(this, name);
			break;
		case ArgType::INT64:
			newElem = new Int64Arg(this, name);
			break;
		case ArgType::UINT32:
			newElem = new UInt32Arg(this, name);
			break;
		case ArgType::UINT64:
			newElem = new UInt64Arg(this, name);
			break;
		case ArgType::FLOAT:
			newElem = new FloatArg(this, name);
			break;
		default:
			newElem = new StringArg(this, name);
		break;
	}

	// try to insert the element, fail on name duplicate
	auto elem = _argsId.insert(std::pair<std::string, uint32_t>(name, _argsInfos.size()));

	// check name duplication
	if (!elem.second) {
		logErr("argument name \"" << name << "\" is already taken");
		delete newElem;
		return (*_argsInfos[elem.first->second]);  // return the existing element
	}

	_argsInfos.push_back(newElem);
	return (*_argsInfos.back());  // return the new element
}

void	ArgsParser::init() {
	// fill _opts string
	for (auto &&argInfos : _argsInfos) {
		if (!argInfos->getRequired()) {
			// fill shortName string
			if (argInfos->getShortName() != A_NO_NAME) {
				_opts += argInfos->getShortName();
				if (argInfos->needArgument()) {
					_opts += ':';
				}
			}
			// fill longName struct
			if (!argInfos->getLongName().empty()) {
				_longOpts.push_back({
					argInfos->getLongName().c_str(),
					argInfos->needArgument() ? required_argument : no_argument, NULL,
					argInfos->getShortName() != A_NO_NAME ? argInfos->getShortName() : 0
				});
			}
		}
	}

	_longOpts.push_back({NULL, 0, NULL, 0});
}

// The variable optind is the index of the next element to be processed in argv.
// The system initializes this value to 1. The caller can reset it to 1 to restart scanning of the same argv,
// or when scanning a new argument vector.

// If the first character of optstring is '+' or the environment variable POSIXLY_CORRECT is set,
// then option processing stops as soon as a nonoption argument is encountered

void	ArgsParser::parseArgs() {
	// int	opt;
	// int	longIndex = 0;
	(void)_ac;

	init();  // init getopt_long args

	usage();

	for (auto &&argInfos : _argsInfos) {
		std::cout << "\n\n======================================================" << std::endl;
		std::cout << " Test arg type [ " << ArgType::enumNames[argInfos->getType()] << " ]" << std::endl;
		std::cout << "======================================================" << std::endl;

		switch (argInfos->getType()) {
			case ArgType::BOOL:
				 {
					auto val = reinterpret_cast<BoolArg *>(argInfos)->getVal();
					std::cout << "[BOOL]" << argInfos->getName() << " ";
					if (val.second) {
						std::cout << "val: " << std::boolalpha << val.first << std::endl;
					}
					else {
						std::cout << "empty" << std::endl;
					}

					std::vector<std::string> okStrs = {
						"true", "True", "tRuE", " 	trUe  	",
						"t", "T", " 	t 	", "1", " 1   	",
						"false", "fALse", "  	 fAlse",
						"f", "  F 	", "0", "  0 	"
					};
					std::vector<std::string> badStrs = {
						"truee", "11", "1 1", "tr ue", "falsee", "00", "0 0", "fa lse"
					};

					std::cout << "______ should be ok" << std::endl;
					std::cout << "________________________" << std::endl;
					for (std::string const &okStr : okStrs) {
						std::cout << "___" << std::endl;
						argInfos->setVal(okStr);
						val = reinterpret_cast<BoolArg *>(argInfos)->getVal();
						std::cout << "\"" << okStr << "\" => ";
						if (val.second) {
							std::cout << std::boolalpha << val.first << std::endl;
						}
						else {
							std::cout << "empty" << std::endl;
						}
					}

					std::cout << "\n___________ should fail" << std::endl;
					std::cout << "________________________" << std::endl;
					for (std::string const &badStr : badStrs) {
						std::cout << "___" << std::endl;
						argInfos->setVal(badStr);
						val = reinterpret_cast<BoolArg *>(argInfos)->getVal();
						std::cout << "\"" << badStr << "\" => ";
						if (val.second) {
							std::cout << std::boolalpha << val.first << std::endl;
						}
						else {
							std::cout << "empty" << std::endl;
						}
					}
				}
				break;
			case ArgType::INT32:
				 {
					auto val = reinterpret_cast<Int32Arg *>(argInfos)->getVal();
					std::cout << "[INT32]" << argInfos->getName() << " ";
					if (val.second) {
						std::cout << "val: " << val.first << std::endl;
					}
					else {
						std::cout << "empty" << std::endl;
					}
					{
						std::cout << "______ should be ok" << std::endl;
						std::string input = "42";
						argInfos->setVal(input);
						val = reinterpret_cast<Int32Arg *>(argInfos)->getVal();
						std::cout << "\"" << input << "\" => ";
						if (val.second) {
							std::cout << std::boolalpha << val.first << std::endl;
						}
						else {
							std::cout << "empty" << std::endl;
						}
					}
					{
						std::cout << "______ should be ok" << std::endl;
						std::string input = "0";
						argInfos->setVal(input);
						val = reinterpret_cast<Int32Arg *>(argInfos)->getVal();
						std::cout << "\"" << input << "\" => ";
						if (val.second) {
							std::cout << std::boolalpha << val.first << std::endl;
						}
						else {
							std::cout << "empty" << std::endl;
						}
					}
					{
						std::cout << "______ should be ok" << std::endl;
						std::string input = "   00042aaa  ";
						argInfos->setVal(input);
						val = reinterpret_cast<Int32Arg *>(argInfos)->getVal();
						std::cout << "\"" << input << "\" => ";
						if (val.second) {
							std::cout << std::boolalpha << val.first << std::endl;
						}
						else {
							std::cout << "empty" << std::endl;
						}
					}
					{
						std::cout << "______ should fail to convert" << std::endl;
						std::string input = "aa42";
						argInfos->setVal(input);
						val = reinterpret_cast<Int32Arg *>(argInfos)->getVal();
						std::cout << "\"" << input << "\" => ";
						if (val.second) {
							std::cout << std::boolalpha << val.first << std::endl;
						}
						else {
							std::cout << "empty" << std::endl;
						}
					}
					{
						std::cout << "______ should fail to convert" << std::endl;
						std::string input = "";
						argInfos->setVal(input);
						val = reinterpret_cast<Int32Arg *>(argInfos)->getVal();
						std::cout << "\"" << input << "\" => ";
						if (val.second) {
							std::cout << std::boolalpha << val.first << std::endl;
						}
						else {
							std::cout << "empty" << std::endl;
						}
					}
					{
						std::cout << "______ should work" << std::endl;
						std::string input = "-2147483648";
						argInfos->setVal(input);
						val = reinterpret_cast<Int32Arg *>(argInfos)->getVal();
						std::cout << "\"" << input << "\" => ";
						if (val.second) {
							std::cout << std::boolalpha << val.first << std::endl;
						}
						else {
							std::cout << "empty" << std::endl;
						}
					}
					{
						std::cout << "______ should underflow" << std::endl;
						std::string input = "-2147483649";
						argInfos->setVal(input);
						val = reinterpret_cast<Int32Arg *>(argInfos)->getVal();
						std::cout << "\"" << input << "\" => ";
						if (val.second) {
							std::cout << std::boolalpha << val.first << std::endl;
						}
						else {
							std::cout << "empty" << std::endl;
						}
					}
					{
						std::cout << "______ should work" << std::endl;
						std::string input = "2147483647";
						argInfos->setVal(input);
						val = reinterpret_cast<Int32Arg *>(argInfos)->getVal();
						std::cout << "\"" << input << "\" => ";
						if (val.second) {
							std::cout << std::boolalpha << val.first << std::endl;
						}
						else {
							std::cout << "empty" << std::endl;
						}
					}
					{
						std::cout << "______ should overflow" << std::endl;
						std::string input = "2147483648";
						argInfos->setVal(input);
						val = reinterpret_cast<Int32Arg *>(argInfos)->getVal();
						std::cout << "\"" << input << "\" => ";
						if (val.second) {
							std::cout << std::boolalpha << val.first << std::endl;
						}
						else {
							std::cout << "empty" << std::endl;
						}
					}
					{
						std::cout << "______ should overflow" << std::endl;
						std::string input = "999999999999999999999999999999999999999999999999"
							"999999999999999999999999999999999999999999999999"
							"999999999999999999999999999999999999999999999999";
						argInfos->setVal(input);
						val = reinterpret_cast<Int32Arg *>(argInfos)->getVal();
						std::cout << "\"" << input << "\" => ";
						if (val.second) {
							std::cout << std::boolalpha << val.first << std::endl;
						}
						else {
							std::cout << "empty" << std::endl;
						}
					}
					// test min max
					{
						std::cout << "______ should work" << std::endl;
						std::string input = "1";
						argInfos->setVal(input);
						argInfos->setMinI32(1);
						val = reinterpret_cast<Int32Arg *>(argInfos)->getVal();
						std::cout << "\"" << input << "\" => ";
						if (val.second) {
							std::cout << std::boolalpha << val.first << std::endl;
						}
						else {
							std::cout << "empty" << std::endl;
						}
					}
					{
						std::cout << "______ should fail input < min 1" << std::endl;
						std::string input = "0";
						argInfos->setVal(input);
						argInfos->setMinI32(1);
						val = reinterpret_cast<Int32Arg *>(argInfos)->getVal();
						std::cout << "\"" << input << "\" => ";
						if (val.second) {
							std::cout << std::boolalpha << val.first << std::endl;
						}
						else {
							std::cout << "empty" << std::endl;
						}
					}
					{
						std::cout << "______ should work" << std::endl;
						std::string input = "2";
						argInfos->setVal(input);
						argInfos->setMaxI32(2);
						val = reinterpret_cast<Int32Arg *>(argInfos)->getVal();
						std::cout << "\"" << input << "\" => ";
						if (val.second) {
							std::cout << std::boolalpha << val.first << std::endl;
						}
						else {
							std::cout << "empty" << std::endl;
						}
					}
					 {
						std::cout << "______ should fail input > max 2" << std::endl;
						std::string input = "3";
						argInfos->setVal(input);
						argInfos->setMinI32(1);
						val = reinterpret_cast<Int32Arg *>(argInfos)->getVal();
						std::cout << "\"" << input << "\" => ";
						if (val.second) {
							std::cout << std::boolalpha << val.first << std::endl;
						}
						else {
							std::cout << "empty" << std::endl;
						}
					}
				}
				break;
			case ArgType::INT64:
				 {
					auto val = reinterpret_cast<Int64Arg *>(argInfos)->getVal();
					std::cout << "[INT32]" << argInfos->getName() << " ";
					if (val.second) {
						std::cout << "val: " << val.first << std::endl;
					}
					else {
						std::cout << "empty" << std::endl;
					}
					{
						std::cout << "______ should be ok" << std::endl;
						std::string input = "42";
						argInfos->setVal(input);
						val = reinterpret_cast<Int64Arg *>(argInfos)->getVal();
						std::cout << "\"" << input << "\" => ";
						if (val.second) {
							std::cout << std::boolalpha << val.first << std::endl;
						}
						else {
							std::cout << "empty" << std::endl;
						}
					}
					{
						std::cout << "______ should be ok" << std::endl;
						std::string input = "0";
						argInfos->setVal(input);
						val = reinterpret_cast<Int64Arg *>(argInfos)->getVal();
						std::cout << "\"" << input << "\" => ";
						if (val.second) {
							std::cout << std::boolalpha << val.first << std::endl;
						}
						else {
							std::cout << "empty" << std::endl;
						}
					}
					{
						std::cout << "______ should be ok" << std::endl;
						std::string input = "   00042aaa  ";
						argInfos->setVal(input);
						val = reinterpret_cast<Int64Arg *>(argInfos)->getVal();
						std::cout << "\"" << input << "\" => ";
						if (val.second) {
							std::cout << std::boolalpha << val.first << std::endl;
						}
						else {
							std::cout << "empty" << std::endl;
						}
					}
					{
						std::cout << "______ should fail to convert" << std::endl;
						std::string input = "aa42";
						argInfos->setVal(input);
						val = reinterpret_cast<Int64Arg *>(argInfos)->getVal();
						std::cout << "\"" << input << "\" => ";
						if (val.second) {
							std::cout << std::boolalpha << val.first << std::endl;
						}
						else {
							std::cout << "empty" << std::endl;
						}
					}
					{
						std::cout << "______ should fail to convert" << std::endl;
						std::string input = "";
						argInfos->setVal(input);
						val = reinterpret_cast<Int64Arg *>(argInfos)->getVal();
						std::cout << "\"" << input << "\" => ";
						if (val.second) {
							std::cout << std::boolalpha << val.first << std::endl;
						}
						else {
							std::cout << "empty" << std::endl;
						}
					}
					{
						std::cout << "______ should work" << std::endl;
						std::string input = "-9223372036854775808";
						argInfos->setVal(input);
						val = reinterpret_cast<Int64Arg *>(argInfos)->getVal();
						std::cout << "\"" << input << "\" => ";
						if (val.second) {
							std::cout << std::boolalpha << val.first << std::endl;
						}
						else {
							std::cout << "empty" << std::endl;
						}
					}
					{
						std::cout << "______ should underflow" << std::endl;
						std::string input = "-9223372036854775809";
						argInfos->setVal(input);
						val = reinterpret_cast<Int64Arg *>(argInfos)->getVal();
						std::cout << "\"" << input << "\" => ";
						if (val.second) {
							std::cout << std::boolalpha << val.first << std::endl;
						}
						else {
							std::cout << "empty" << std::endl;
						}
					}
					{
						std::cout << "______ should work" << std::endl;
						std::string input = "9223372036854775807";
						argInfos->setVal(input);
						val = reinterpret_cast<Int64Arg *>(argInfos)->getVal();
						std::cout << "\"" << input << "\" => ";
						if (val.second) {
							std::cout << std::boolalpha << val.first << std::endl;
						}
						else {
							std::cout << "empty" << std::endl;
						}
					}
					{
						std::cout << "______ should overflow" << std::endl;
						std::string input = "9223372036854775808";
						argInfos->setVal(input);
						val = reinterpret_cast<Int64Arg *>(argInfos)->getVal();
						std::cout << "\"" << input << "\" => ";
						if (val.second) {
							std::cout << std::boolalpha << val.first << std::endl;
						}
						else {
							std::cout << "empty" << std::endl;
						}
					}
					{
						std::cout << "______ should overflow" << std::endl;
						std::string input = "999999999999999999999999999999999999999999999999"
							"999999999999999999999999999999999999999999999999"
							"999999999999999999999999999999999999999999999999";
						argInfos->setVal(input);
						val = reinterpret_cast<Int64Arg *>(argInfos)->getVal();
						std::cout << "\"" << input << "\" => ";
						if (val.second) {
							std::cout << std::boolalpha << val.first << std::endl;
						}
						else {
							std::cout << "empty" << std::endl;
						}
					}
					// test min max
					{
						std::cout << "______ should work" << std::endl;
						std::string input = "1";
						argInfos->setVal(input);
						argInfos->setMinI64(1);
						val = reinterpret_cast<Int64Arg *>(argInfos)->getVal();
						std::cout << "\"" << input << "\" => ";
						if (val.second) {
							std::cout << std::boolalpha << val.first << std::endl;
						}
						else {
							std::cout << "empty" << std::endl;
						}
					}
					{
						std::cout << "______ should fail input < min 1" << std::endl;
						std::string input = "0";
						argInfos->setVal(input);
						argInfos->setMinI64(1);
						val = reinterpret_cast<Int64Arg *>(argInfos)->getVal();
						std::cout << "\"" << input << "\" => ";
						if (val.second) {
							std::cout << std::boolalpha << val.first << std::endl;
						}
						else {
							std::cout << "empty" << std::endl;
						}
					}
					{
						std::cout << "______ should work" << std::endl;
						std::string input = "2";
						argInfos->setVal(input);
						argInfos->setMaxI64(2);
						val = reinterpret_cast<Int64Arg *>(argInfos)->getVal();
						std::cout << "\"" << input << "\" => ";
						if (val.second) {
							std::cout << std::boolalpha << val.first << std::endl;
						}
						else {
							std::cout << "empty" << std::endl;
						}
					}
					 {
						std::cout << "______ should fail input > max 2" << std::endl;
						std::string input = "3";
						argInfos->setVal(input);
						argInfos->setMinI64(1);
						val = reinterpret_cast<Int64Arg *>(argInfos)->getVal();
						std::cout << "\"" << input << "\" => ";
						if (val.second) {
							std::cout << std::boolalpha << val.first << std::endl;
						}
						else {
							std::cout << "empty" << std::endl;
						}
					}
				}
				break;
			case ArgType::UINT32:
				 {
					auto val = reinterpret_cast<UInt32Arg *>(argInfos)->getVal();
					std::cout << "[INT32]" << argInfos->getName() << " ";
					if (val.second) {
						std::cout << "val: " << val.first << std::endl;
					}
					else {
						std::cout << "empty" << std::endl;
					}
					{
						std::cout << "______ should be ok" << std::endl;
						std::string input = "42";
						argInfos->setVal(input);
						val = reinterpret_cast<UInt32Arg *>(argInfos)->getVal();
						std::cout << "\"" << input << "\" => ";
						if (val.second) {
							std::cout << std::boolalpha << val.first << std::endl;
						}
						else {
							std::cout << "empty" << std::endl;
						}
					}
					{
						std::cout << "______ should be ok" << std::endl;
						std::string input = "0";
						argInfos->setVal(input);
						val = reinterpret_cast<UInt32Arg *>(argInfos)->getVal();
						std::cout << "\"" << input << "\" => ";
						if (val.second) {
							std::cout << std::boolalpha << val.first << std::endl;
						}
						else {
							std::cout << "empty" << std::endl;
						}
					}
					{
						std::cout << "______ should be ok" << std::endl;
						std::string input = "   00042aaa  ";
						argInfos->setVal(input);
						val = reinterpret_cast<UInt32Arg *>(argInfos)->getVal();
						std::cout << "\"" << input << "\" => ";
						if (val.second) {
							std::cout << std::boolalpha << val.first << std::endl;
						}
						else {
							std::cout << "empty" << std::endl;
						}
					}
					{
						std::cout << "______ should fail to convert" << std::endl;
						std::string input = "aa42";
						argInfos->setVal(input);
						val = reinterpret_cast<UInt32Arg *>(argInfos)->getVal();
						std::cout << "\"" << input << "\" => ";
						if (val.second) {
							std::cout << std::boolalpha << val.first << std::endl;
						}
						else {
							std::cout << "empty" << std::endl;
						}
					}
					{
						std::cout << "______ should fail to convert" << std::endl;
						std::string input = "";
						argInfos->setVal(input);
						val = reinterpret_cast<UInt32Arg *>(argInfos)->getVal();
						std::cout << "\"" << input << "\" => ";
						if (val.second) {
							std::cout << std::boolalpha << val.first << std::endl;
						}
						else {
							std::cout << "empty" << std::endl;
						}
					}
					{
						std::cout << "______ should work" << std::endl;
						std::string input = "0";
						argInfos->setVal(input);
						val = reinterpret_cast<UInt32Arg *>(argInfos)->getVal();
						std::cout << "\"" << input << "\" => ";
						if (val.second) {
							std::cout << std::boolalpha << val.first << std::endl;
						}
						else {
							std::cout << "empty" << std::endl;
						}
					}
					{
						std::cout << "______ should underflow" << std::endl;
						std::string input = "-1";
						argInfos->setVal(input);
						val = reinterpret_cast<UInt32Arg *>(argInfos)->getVal();
						std::cout << "\"" << input << "\" => ";
						if (val.second) {
							std::cout << std::boolalpha << val.first << std::endl;
						}
						else {
							std::cout << "empty" << std::endl;
						}
					}
					{
						std::cout << "______ should work" << std::endl;
						std::string input = "4294967295";
						argInfos->setVal(input);
						val = reinterpret_cast<UInt32Arg *>(argInfos)->getVal();
						std::cout << "\"" << input << "\" => ";
						if (val.second) {
							std::cout << std::boolalpha << val.first << std::endl;
						}
						else {
							std::cout << "empty" << std::endl;
						}
					}
					{
						std::cout << "______ should overflow" << std::endl;
						std::string input = "4294967296";
						argInfos->setVal(input);
						val = reinterpret_cast<UInt32Arg *>(argInfos)->getVal();
						std::cout << "\"" << input << "\" => ";
						if (val.second) {
							std::cout << std::boolalpha << val.first << std::endl;
						}
						else {
							std::cout << "empty" << std::endl;
						}
					}
					{
						std::cout << "______ should overflow" << std::endl;
						std::string input = "999999999999999999999999999999999999999999999999"
							"999999999999999999999999999999999999999999999999"
							"999999999999999999999999999999999999999999999999";
						argInfos->setVal(input);
						val = reinterpret_cast<UInt32Arg *>(argInfos)->getVal();
						std::cout << "\"" << input << "\" => ";
						if (val.second) {
							std::cout << std::boolalpha << val.first << std::endl;
						}
						else {
							std::cout << "empty" << std::endl;
						}
					}
					// test min max
					{
						std::cout << "______ should work" << std::endl;
						std::string input = "1";
						argInfos->setVal(input);
						argInfos->setMinUI32(1);
						val = reinterpret_cast<UInt32Arg *>(argInfos)->getVal();
						std::cout << "\"" << input << "\" => ";
						if (val.second) {
							std::cout << std::boolalpha << val.first << std::endl;
						}
						else {
							std::cout << "empty" << std::endl;
						}
					}
					{
						std::cout << "______ should fail input < min 1" << std::endl;
						std::string input = "0";
						argInfos->setVal(input);
						argInfos->setMinUI32(1);
						val = reinterpret_cast<UInt32Arg *>(argInfos)->getVal();
						std::cout << "\"" << input << "\" => ";
						if (val.second) {
							std::cout << std::boolalpha << val.first << std::endl;
						}
						else {
							std::cout << "empty" << std::endl;
						}
					}
					{
						std::cout << "______ should work" << std::endl;
						std::string input = "2";
						argInfos->setVal(input);
						argInfos->setMaxUI32(2);
						val = reinterpret_cast<UInt32Arg *>(argInfos)->getVal();
						std::cout << "\"" << input << "\" => ";
						if (val.second) {
							std::cout << std::boolalpha << val.first << std::endl;
						}
						else {
							std::cout << "empty" << std::endl;
						}
					}
					 {
						std::cout << "______ should fail input > max 2" << std::endl;
						std::string input = "3";
						argInfos->setVal(input);
						argInfos->setMinUI32(1);
						val = reinterpret_cast<UInt32Arg *>(argInfos)->getVal();
						std::cout << "\"" << input << "\" => ";
						if (val.second) {
							std::cout << std::boolalpha << val.first << std::endl;
						}
						else {
							std::cout << "empty" << std::endl;
						}
					}
				}
				break;
			case ArgType::UINT64:
				 {
					auto val = reinterpret_cast<UInt64Arg *>(argInfos)->getVal();
					std::cout << "[INT32]" << argInfos->getName() << " ";
					if (val.second) {
						std::cout << "val: " << val.first << std::endl;
					}
					else {
						std::cout << "empty" << std::endl;
					}
					{
						std::cout << "______ should be ok" << std::endl;
						std::string input = "42";
						argInfos->setVal(input);
						val = reinterpret_cast<UInt64Arg *>(argInfos)->getVal();
						std::cout << "\"" << input << "\" => ";
						if (val.second) {
							std::cout << std::boolalpha << val.first << std::endl;
						}
						else {
							std::cout << "empty" << std::endl;
						}
					}
					{
						std::cout << "______ should be ok" << std::endl;
						std::string input = "0";
						argInfos->setVal(input);
						val = reinterpret_cast<UInt64Arg *>(argInfos)->getVal();
						std::cout << "\"" << input << "\" => ";
						if (val.second) {
							std::cout << std::boolalpha << val.first << std::endl;
						}
						else {
							std::cout << "empty" << std::endl;
						}
					}
					{
						std::cout << "______ should be ok" << std::endl;
						std::string input = "   00042aaa  ";
						argInfos->setVal(input);
						val = reinterpret_cast<UInt64Arg *>(argInfos)->getVal();
						std::cout << "\"" << input << "\" => ";
						if (val.second) {
							std::cout << std::boolalpha << val.first << std::endl;
						}
						else {
							std::cout << "empty" << std::endl;
						}
					}
					{
						std::cout << "______ should fail to convert" << std::endl;
						std::string input = "aa42";
						argInfos->setVal(input);
						val = reinterpret_cast<UInt64Arg *>(argInfos)->getVal();
						std::cout << "\"" << input << "\" => ";
						if (val.second) {
							std::cout << std::boolalpha << val.first << std::endl;
						}
						else {
							std::cout << "empty" << std::endl;
						}
					}
					{
						std::cout << "______ should fail to convert" << std::endl;
						std::string input = "";
						argInfos->setVal(input);
						val = reinterpret_cast<UInt64Arg *>(argInfos)->getVal();
						std::cout << "\"" << input << "\" => ";
						if (val.second) {
							std::cout << std::boolalpha << val.first << std::endl;
						}
						else {
							std::cout << "empty" << std::endl;
						}
					}
					{
						std::cout << "______ should work" << std::endl;
						std::string input = "0";
						argInfos->setVal(input);
						val = reinterpret_cast<UInt64Arg *>(argInfos)->getVal();
						std::cout << "\"" << input << "\" => ";
						if (val.second) {
							std::cout << std::boolalpha << val.first << std::endl;
						}
						else {
							std::cout << "empty" << std::endl;
						}
					}
					{
						std::cout << "______ should underflow" << std::endl;
						std::string input = "-1";
						argInfos->setVal(input);
						val = reinterpret_cast<UInt64Arg *>(argInfos)->getVal();
						std::cout << "\"" << input << "\" => ";
						if (val.second) {
							std::cout << std::boolalpha << val.first << std::endl;
						}
						else {
							std::cout << "empty" << std::endl;
						}
					}
					{
						std::cout << "______ should work" << std::endl;
						std::string input = "18446744073709551615";
						argInfos->setVal(input);
						val = reinterpret_cast<UInt64Arg *>(argInfos)->getVal();
						std::cout << "\"" << input << "\" => ";
						if (val.second) {
							std::cout << std::boolalpha << val.first << std::endl;
						}
						else {
							std::cout << "empty" << std::endl;
						}
					}
					{
						std::cout << "______ should overflow" << std::endl;
						std::string input = "18446744073709551616";
						argInfos->setVal(input);
						val = reinterpret_cast<UInt64Arg *>(argInfos)->getVal();
						std::cout << "\"" << input << "\" => ";
						if (val.second) {
							std::cout << std::boolalpha << val.first << std::endl;
						}
						else {
							std::cout << "empty" << std::endl;
						}
					}
					{
						std::cout << "______ should overflow" << std::endl;
						std::string input = "999999999999999999999999999999999999999999999999"
							"999999999999999999999999999999999999999999999999"
							"999999999999999999999999999999999999999999999999";
						argInfos->setVal(input);
						val = reinterpret_cast<UInt64Arg *>(argInfos)->getVal();
						std::cout << "\"" << input << "\" => ";
						if (val.second) {
							std::cout << std::boolalpha << val.first << std::endl;
						}
						else {
							std::cout << "empty" << std::endl;
						}
					}
					// test min max
					{
						std::cout << "______ should work" << std::endl;
						std::string input = "1";
						argInfos->setVal(input);
						argInfos->setMinUI64(1);
						val = reinterpret_cast<UInt64Arg *>(argInfos)->getVal();
						std::cout << "\"" << input << "\" => ";
						if (val.second) {
							std::cout << std::boolalpha << val.first << std::endl;
						}
						else {
							std::cout << "empty" << std::endl;
						}
					}
					{
						std::cout << "______ should fail input < min 1" << std::endl;
						std::string input = "0";
						argInfos->setVal(input);
						argInfos->setMinUI64(1);
						val = reinterpret_cast<UInt64Arg *>(argInfos)->getVal();
						std::cout << "\"" << input << "\" => ";
						if (val.second) {
							std::cout << std::boolalpha << val.first << std::endl;
						}
						else {
							std::cout << "empty" << std::endl;
						}
					}
					{
						std::cout << "______ should work" << std::endl;
						std::string input = "2";
						argInfos->setVal(input);
						argInfos->setMaxUI64(2);
						val = reinterpret_cast<UInt64Arg *>(argInfos)->getVal();
						std::cout << "\"" << input << "\" => ";
						if (val.second) {
							std::cout << std::boolalpha << val.first << std::endl;
						}
						else {
							std::cout << "empty" << std::endl;
						}
					}
					 {
						std::cout << "______ should fail input > max 2" << std::endl;
						std::string input = "3";
						argInfos->setVal(input);
						argInfos->setMinUI64(1);
						val = reinterpret_cast<UInt64Arg *>(argInfos)->getVal();
						std::cout << "\"" << input << "\" => ";
						if (val.second) {
							std::cout << std::boolalpha << val.first << std::endl;
						}
						else {
							std::cout << "empty" << std::endl;
						}
					}
				}
				break;
			case ArgType::FLOAT:
				 {
					auto val = reinterpret_cast<FloatArg *>(argInfos)->getVal();
					std::cout << "[INT32]" << argInfos->getName() << " ";
					if (val.second) {
						std::cout << "val: " << val.first << std::endl;
					}
					else {
						std::cout << "empty" << std::endl;
					}
					{
						std::cout << "______ should be ok" << std::endl;
						std::string input = "42";
						argInfos->setVal(input);
						val = reinterpret_cast<FloatArg *>(argInfos)->getVal();
						std::cout << "\"" << input << "\" => ";
						if (val.second) {
							std::cout << std::boolalpha << val.first << std::endl;
						}
						else {
							std::cout << "empty" << std::endl;
						}
					}
					{
						std::cout << "______ should be ok" << std::endl;
						std::string input = "0";
						argInfos->setVal(input);
						val = reinterpret_cast<FloatArg *>(argInfos)->getVal();
						std::cout << "\"" << input << "\" => ";
						if (val.second) {
							std::cout << std::boolalpha << val.first << std::endl;
						}
						else {
							std::cout << "empty" << std::endl;
						}
					}
					{
						std::cout << "______ should be ok" << std::endl;
						std::string input = "   00042aaa  ";
						argInfos->setVal(input);
						val = reinterpret_cast<FloatArg *>(argInfos)->getVal();
						std::cout << "\"" << input << "\" => ";
						if (val.second) {
							std::cout << std::boolalpha << val.first << std::endl;
						}
						else {
							std::cout << "empty" << std::endl;
						}
					}
					{
						std::cout << "______ should fail to convert" << std::endl;
						std::string input = "aa42";
						argInfos->setVal(input);
						val = reinterpret_cast<FloatArg *>(argInfos)->getVal();
						std::cout << "\"" << input << "\" => ";
						if (val.second) {
							std::cout << std::boolalpha << val.first << std::endl;
						}
						else {
							std::cout << "empty" << std::endl;
						}
					}
					{
						std::cout << "______ should fail to convert" << std::endl;
						std::string input = "";
						argInfos->setVal(input);
						val = reinterpret_cast<FloatArg *>(argInfos)->getVal();
						std::cout << "\"" << input << "\" => ";
						if (val.second) {
							std::cout << std::boolalpha << val.first << std::endl;
						}
						else {
							std::cout << "empty" << std::endl;
						}
					}
					{
						std::cout << "______ should work" << std::endl;
						std::string input = "-340282346638528859811704183484516925440.000000";
						argInfos->setVal(input);
						val = reinterpret_cast<FloatArg *>(argInfos)->getVal();
						std::cout << "\"" << input << "\" => ";
						if (val.second) {
							std::cout << std::boolalpha << val.first << std::endl;
						}
						else {
							std::cout << "empty" << std::endl;
						}
					}
					{
						std::cout << "______ should underflow" << std::endl;
						std::string input = "-340282346638528859811704183484516925440.000001";
						argInfos->setVal(input);
						val = reinterpret_cast<FloatArg *>(argInfos)->getVal();
						std::cout << "\"" << input << "\" => ";
						if (val.second) {
							std::cout << std::boolalpha << val.first << std::endl;
						}
						else {
							std::cout << "empty" << std::endl;
						}
					}
					{
						std::cout << "______ should work" << std::endl;
						std::string input = "340282346638528859811704183484516925440.000000";
						argInfos->setVal(input);
						val = reinterpret_cast<FloatArg *>(argInfos)->getVal();
						std::cout << "\"" << input << "\" => ";
						if (val.second) {
							std::cout << std::boolalpha << val.first << std::endl;
						}
						else {
							std::cout << "empty" << std::endl;
						}
					}
					{
						std::cout << "______ should overflow" << std::endl;
						std::string input = "940282346638528859811704183484516925440.000000";
						argInfos->setVal(input);
						val = reinterpret_cast<FloatArg *>(argInfos)->getVal();
						std::cout << "\"" << input << "\" => ";
						if (val.second) {
							std::cout << std::boolalpha << val.first << std::endl;
						}
						else {
							std::cout << "empty" << std::endl;
						}
					}
					{
						std::cout << "______ should overflow" << std::endl;
						std::string input = "999999999999999999999999999999999999999999999999"
							"999999999999999999999999999999999999999999999999"
							"999999999999999999999999999999999999999999999999";
						argInfos->setVal(input);
						val = reinterpret_cast<FloatArg *>(argInfos)->getVal();
						std::cout << "\"" << input << "\" => ";
						if (val.second) {
							std::cout << std::boolalpha << val.first << std::endl;
						}
						else {
							std::cout << "empty" << std::endl;
						}
					}
					// test min max
					{
						std::cout << "______ should work" << std::endl;
						std::string input = "1";
						argInfos->setVal(input);
						argInfos->setMinF(1);
						val = reinterpret_cast<FloatArg *>(argInfos)->getVal();
						std::cout << "\"" << input << "\" => ";
						if (val.second) {
							std::cout << std::boolalpha << val.first << std::endl;
						}
						else {
							std::cout << "empty" << std::endl;
						}
					}
					{
						std::cout << "______ should fail input < min 1" << std::endl;
						std::string input = "0";
						argInfos->setVal(input);
						argInfos->setMinF(1);
						val = reinterpret_cast<FloatArg *>(argInfos)->getVal();
						std::cout << "\"" << input << "\" => ";
						if (val.second) {
							std::cout << std::boolalpha << val.first << std::endl;
						}
						else {
							std::cout << "empty" << std::endl;
						}
					}
					{
						std::cout << "______ should work" << std::endl;
						std::string input = "2";
						argInfos->setVal(input);
						argInfos->setMaxF(2);
						val = reinterpret_cast<FloatArg *>(argInfos)->getVal();
						std::cout << "\"" << input << "\" => ";
						if (val.second) {
							std::cout << std::boolalpha << val.first << std::endl;
						}
						else {
							std::cout << "empty" << std::endl;
						}
					}
					 {
						std::cout << "______ should fail input > max 2" << std::endl;
						std::string input = "3";
						argInfos->setVal(input);
						argInfos->setMinF(1);
						val = reinterpret_cast<FloatArg *>(argInfos)->getVal();
						std::cout << "\"" << input << "\" => ";
						if (val.second) {
							std::cout << std::boolalpha << val.first << std::endl;
						}
						else {
							std::cout << "empty" << std::endl;
						}
					}
				}
				break;
			default:
				 {
					auto val = reinterpret_cast<StringArg *>(argInfos)->getVal();
					std::cout << "[STRING]" << argInfos->getName() << " ";
					if (val.second) {
						std::cout << "val: " << val.first << std::endl;
					}
					else {
						std::cout << "empty" << std::endl;
					}
					{
						std::cout << "______ should fail for empty string" << std::endl;
						std::string input = "";
						argInfos->setVal(input);
						val = reinterpret_cast<StringArg *>(argInfos)->getVal();
						std::cout << "\"" << input << "\" => ";
						if (val.second) {
							std::cout << std::boolalpha << val.first << std::endl;
						}
						else {
							std::cout << "empty" << std::endl;
						}
					}
					{
						std::cout << "______ should be ok" << std::endl;
						std::string input = "aa";
						argInfos->setVal(input);
						val = reinterpret_cast<StringArg *>(argInfos)->getVal();
						std::cout << "\"" << input << "\" => ";
						if (val.second) {
							std::cout << std::boolalpha << val.first << std::endl;
						}
						else {
							std::cout << "empty" << std::endl;
						}
					}
					{
						std::cout << "______ should be ok len == 2" << std::endl;
						std::string input = "bb";
						argInfos->setMinLength(2);
						argInfos->setVal(input);
						val = reinterpret_cast<StringArg *>(argInfos)->getVal();
						std::cout << "\"" << input << "\" => ";
						if (val.second) {
							std::cout << std::boolalpha << val.first << std::endl;
						}
						else {
							std::cout << "empty" << std::endl;
						}
					}
					{
						std::cout << "______ should fail because len < 3" << std::endl;
						std::string input = "cc";
						argInfos->setMinLength(3);
						argInfos->setVal(input);
						val = reinterpret_cast<StringArg *>(argInfos)->getVal();
						std::cout << "\"" << input << "\" => ";
						if (val.second) {
							std::cout << std::boolalpha << val.first << std::endl;
						}
						else {
							std::cout << "empty" << std::endl;
						}
					}
					{
						std::cout << "______ should be ok" << std::endl;
						std::string input = "dddd";
						argInfos->setMaxLength(4);
						argInfos->setVal(input);
						val = reinterpret_cast<StringArg *>(argInfos)->getVal();
						std::cout << "\"" << input << "\" => ";
						if (val.second) {
							std::cout << std::boolalpha << val.first << std::endl;
						}
						else {
							std::cout << "empty" << std::endl;
						}
					}
					 {
						std::cout << "______ should fail because len > 4" << std::endl;
						std::string input = "eeeee";
						argInfos->setMaxLength(4);
						argInfos->setVal(input);
						val = reinterpret_cast<StringArg *>(argInfos)->getVal();
						std::cout << "\"" << input << "\" => ";
						if (val.second) {
							std::cout << std::boolalpha << val.first << std::endl;
						}
						else {
							std::cout << "empty" << std::endl;
						}
					}
				}
			break;
		}
	}

	// while ((opt = getopt_long(_ac, _av, _opts.c_str(), _longOpts.data(), &longIndex)) != -1) {
	// 	std::cout << "opt: " << static_cast<char>(opt) << std::endl;
	// 	switch (opt) {
	// 		case 0:
	// 			std::cout << "long opt: " << _longOpts[longIndex].name << std::endl;
	// 			if (optarg) {
	// 				std::cout << "with arg \"" << optarg << "\"" << std::endl;
	// 			}
	// 			break;
	// 		case 'w':
	// 			std::cout << "optarg: " << optarg << std::endl;
	// 			break;
	// 		case 'g':
	// 			std::cout << "optarg: " << optarg << std::endl;
	// 			break;
	// 		case 's':
	// 			std::cout << "optarg: " << optarg << std::endl;
	// 			break;
	// 		case 'b':
	// 			std::cout << "optarg: " << optarg << std::endl;
	// 			break;
	// 		case 'u': case '?': default:
	// 			std::cout << "// usage();" << std::endl;
	// 			usage();
	// 			break;
	// 		break;
	// 	}
	// }
}

void	ArgsParser::setProgDescr(std::string const &progDescr) { _progDescr = progDescr; }

// -- Exceptions errors --------------------------------------------------------
ArgsParser::ArgsParserException::ArgsParserException()
: std::runtime_error("[ArgsParserError]") {}

ArgsParser::ArgsParserException::ArgsParserException(const char* what_arg)
: std::runtime_error(std::string(std::string("[ArgsParserError] ") + what_arg).c_str()) {}

