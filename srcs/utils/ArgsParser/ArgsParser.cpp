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

// test optionals name validity
bool	ArgsParser::checkOptsAvailability(std::string const &longName, char shortName) {
	std::string const	errInfo = "setOptional('" + std::string(1, shortName) + \
		"', \"" + longName + "\"): ";

	// refuse empty longName && empty shortName
	if (longName.empty() && shortName == A_NO_NAME) {
		logErr(errInfo << "you need to specify at least a shortName or a longName");
		return EXIT_FAILURE;
	}

	// shortName invalid char
	if (!isalnum(shortName) && shortName != A_NO_NAME) {
		logErr(errInfo << "shortName only accept alphanumeric chars");
		return EXIT_FAILURE;
	}

	// accept only alphanumeric and '-' '_' chars
	auto isInvalidChar = [](char c) {
		return !(isalnum(c) || c == ' ' || c == '-' || c == '_'); };
	// longName invalid char
	if (!longName.empty() && find_if(longName.begin(), longName.end(), isInvalidChar)
		!= longName.end()) {
		logErr(errInfo << "longName only accept alphanumeric, '-' and '_' chars");
		return EXIT_FAILURE;
	}

	// refuse char '-' at the begining of a long/short name
	if (shortName == '-' || longName[0] == '-') {
		logErr(errInfo << "you can't put char '-' at the begining of a long/short name");
		return EXIT_FAILURE;
	}

	// The -W option is reserved by POSIX.2 for implementation extensions
	if (shortName == 'W') {
		logErr(errInfo << "the -W option is reserved by POSIX.2 for implementation extensions");
		return EXIT_FAILURE;
	}

	// The -u option is reserved for usage
	if (shortName == 'u') {
		logErr(errInfo << "The -u short option is reserved for usage");
		return EXIT_FAILURE;
	}

	// The -u option is reserved for usage
	if (longName == "usage") {
		logErr(errInfo << "The --usage long option is reserved for usage");
		return EXIT_FAILURE;
	}

	// check shortName/longName duplicates
	uint32_t	nbDuplicates = std::count_if(std::begin(_argsInfos), std::end(_argsInfos),
		[longName, shortName] (AInfoArg * const argInfos) {
			return (argInfos->getShortName() != A_NO_NAME && shortName != A_NO_NAME && \
				argInfos->getShortName() == shortName) || (!argInfos->getLongName().empty() && argInfos->getLongName() == longName);
		});
	if (nbDuplicates > 0) {
		logErr(errInfo << "duplicate optional arg name: " << "-" << shortName << ", --" << longName);
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
	_opts = 'u';
	_longOpts = {{ "usage", no_argument, NULL, 'u' }};

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
	int	opt;
	int	longIndex = 0;

	init();  // init getopt_long args

	while ((opt = getopt_long(_ac, _av, _opts.c_str(), _longOpts.data(), &longIndex)) != -1) {
		logDebug("opt: " << static_cast<char>(opt));

		// long option
		if (opt == 0) {
				std::cout << "long opt: " << _longOpts[longIndex].name << std::endl;
				if (optarg) {
					std::cout << "with arg \"" << optarg << "\"" << std::endl;
				}
		}
		// show usage and stop
		else if (opt == '?' || opt == 'u' || opt == ':') {
			std::cout << "// usage();" << std::endl;
			// usage();
			break;
		}
		// short option
		else {
			std::cout << "short: '" << opt << "'" << std::endl;
			if (true) {  // ? condition ?
				std::cout << "optarg: " << optarg << std::endl;
			}
		}
	}
}

void	ArgsParser::setProgDescr(std::string const &progDescr) { _progDescr = progDescr; }

// -- Exceptions errors --------------------------------------------------------
ArgsParser::ArgsParserException::ArgsParserException()
: std::runtime_error("[ArgsParserError]") {}

ArgsParser::ArgsParserException::ArgsParserException(const char* what_arg)
: std::runtime_error(std::string(std::string("[ArgsParserError] ") + what_arg).c_str()) {}

