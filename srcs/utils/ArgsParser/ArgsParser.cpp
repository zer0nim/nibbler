#include "ArgsParser.hpp"

#include <algorithm>
#include <utility>

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
		delete argInfos.second;
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
	// print positional arguments
	for (auto &&argInfos : _argsInfos) {
		if (argInfos.second->getRequired()) {
			std::cout << " " COLOR_ULINE << argInfos.second->getName() << COLOR_EOC;
		}
	}
	// print optional arguments
	for (auto &&argInfos : _argsInfos) {
		if (!argInfos.second->getRequired()) {
			if (argInfos.second->getShortName() == A_NO_NAME) {
				std::cout << " [" COLOR_BOLD "--" << argInfos.second->getLongName() << COLOR_EOC;
			}
			else {
				std::cout << " [" COLOR_BOLD "-" << argInfos.second->getShortName() << COLOR_EOC;
			}

			if (argInfos.second->needArgument()) {
				std::cout << " " COLOR_ULINE << argInfos.second->getLongName() << COLOR_ULINE_R;
			}

			std::cout << "]";
		}
	}

	uint32_t	nbPositional = std::count_if(std::begin(_argsInfos), std::end(_argsInfos),
		[] (std::pair<std::string, ArgInfo *> const aPair) {
			return aPair.second->getRequired(); });

	// print positional args help
	if (nbPositional > 0) {
		std::cout << COLOR_ULINE "\n\npositional arguments" COLOR_ULINE_R;
		for (auto &&argInfos : _argsInfos) {
			if (argInfos.second->getRequired()) {
				std::cout << "\n  " COLOR_ULINE << argInfos.second->getName() << COLOR_EOC ":  " << \
				argInfos.second->getHelp() << std::endl;
				std::cout << "  " << *argInfos.second << std::endl;
			}
		}
	}

	// print optional args help
	if (_argsInfos.size() - nbPositional > 0) {
		std::cout << (nbPositional > 0 ? "\n" : "\n\n");
		std::cout << COLOR_ULINE "optional arguments" COLOR_ULINE_R;
		for (auto &&argInfos : _argsInfos) {
			if (!argInfos.second->getRequired()) {
				std::cout << "\n  " COLOR_ULINE << argInfos.second->getName() << COLOR_EOC ":  ";

				// if the short name is available
				if (argInfos.second->getShortName() != A_NO_NAME) {
					std::cout << COLOR_BOLD "-" << argInfos.second->getShortName() << COLOR_EOC;
					if (!argInfos.second->getLongName().empty()) {
						std::cout << ", ";
					}
				}
				if (!argInfos.second->getLongName().empty()) {
					std::cout << COLOR_BOLD "--" << argInfos.second->getLongName() << COLOR_EOC;
				}
				std::cout << "  " << argInfos.second->getHelp() << "\n  " << *argInfos.second << std::endl;
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
		[longName, shortName] (std::pair<std::string, ArgInfo *> const aPair) {
			ArgInfo	const *arg = aPair.second;
			return (arg->getShortName() != A_NO_NAME && shortName != A_NO_NAME && \
				arg->getShortName() == shortName) || (!arg->getLongName().empty() && arg->getLongName() == longName);
		});
	if (nbDuplicates > 0) {
		logErr("duplicate optional arg name: " << "-" << shortName << ", --" << longName);
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}

// create new arg of the specified type, add it to _argsInfos, then return a ref
ArgInfo	&ArgsParser::addArgument(std::string name, ArgType::Enum type) {
	ArgInfo	*newElem = nullptr;

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
	auto elem = _argsInfos.insert(std::pair<std::string, ArgInfo *>(name, newElem));

	// check name duplication
	if (!elem.second) {
		logErr("argument name \"" << name << "\" is already taken");
		delete newElem;
		return *((*elem.first).second);  // return the existing element
	}

	return *((*elem.first).second);
}

void	ArgsParser::init() {
	// fill _opts string
	for (auto &&argInfos : _argsInfos) {
		if (!argInfos.second->getRequired()) {
			// fill shortName string
			if (argInfos.second->getShortName() != A_NO_NAME) {
				_opts += argInfos.second->getShortName();
				if (argInfos.second->needArgument()) {
					_opts += ':';
				}
			}
			// fill longName struct
			if (!argInfos.second->getLongName().empty()) {
				_longOpts.push_back({
					argInfos.second->getLongName().c_str(),
					argInfos.second->needArgument() ? required_argument : no_argument, NULL,
					argInfos.second->getShortName() != A_NO_NAME ? argInfos.second->getShortName() : 0
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
		std::cout << "opt: " << static_cast<char>(opt) << std::endl;
		switch (opt) {
			case 0:
				std::cout << "long opt: " << _longOpts[longIndex].name << std::endl;
				if (optarg) {
					std::cout << "with arg \"" << optarg << "\"" << std::endl;
				}
				break;
			case 'w':
				std::cout << "optarg: " << optarg << std::endl;
				break;
			case 'g':
				std::cout << "optarg: " << optarg << std::endl;
				break;
			case 's':
				std::cout << "optarg: " << optarg << std::endl;
				break;
			case 'b':
				std::cout << "optarg: " << optarg << std::endl;
				break;
			case 'u': case '?': default:
				std::cout << "// usage();" << std::endl;
				usage();
				break;
			break;
		}
	}
}

void	ArgsParser::setProgDescr(std::string const &progDescr) { _progDescr = progDescr; }

// -- Exceptions errors --------------------------------------------------------
ArgsParser::ArgsParserException::ArgsParserException()
: std::runtime_error("[ArgsParserError]") {}

ArgsParser::ArgsParserException::ArgsParserException(const char* what_arg)
: std::runtime_error(std::string(std::string("[ArgsParserError] ") + what_arg).c_str()) {}

