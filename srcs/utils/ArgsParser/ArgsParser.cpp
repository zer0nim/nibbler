#include "ArgsParser.hpp"

#include <algorithm>
#include <set>

#include "Logging.hpp"

ArgsParser::ArgsParser() {
}

ArgsParser::ArgsParser(int ac, char * const *av)
: _ac(ac),
  _av(av) {
}

ArgsParser::~ArgsParser() {
	// free _argsInfos vector
	for (ArgInfo *argInfos : _argsInfos) {
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
	// print args possibilities
	for (auto &&argInfos : _argsInfos) {
		// positional arguments
		if (argInfos->required) {
			std::cout << " " COLOR_BOLD << argInfos->name << COLOR_EOC;
		}
		// optional arguments
		else {
			// if the short option is not available
			if (argInfos->shortName == A_NO_NAME) {
				std::cout << " [" COLOR_BOLD "--" << argInfos->longName << COLOR_EOC;
			}
			else {
				std::cout << " [" COLOR_BOLD "-" << argInfos->shortName << COLOR_EOC;
			}

			// if the arg need a value
			if (!(argInfos->type == ArgType::BOOL && reinterpret_cast<BoolArg *>(argInfos)->storeTrue)) {
				std::cout << " " COLOR_ULINE << argInfos->longName << COLOR_ULINE_R;
			}

			std::cout << "]";
		}
	}

	uint32_t	nbPositional = std::count_if(std::begin(_argsInfos), std::end(_argsInfos),
		[] (ArgInfo * const &arg) { return arg->required; });

	// print positional args help
	if (nbPositional > 0) {
		std::cout << COLOR_ULINE "\n\npositional arguments" COLOR_ULINE_R;
		for (auto &&argInfos : _argsInfos) {
			if (argInfos->required) {
				std::cout << "\n  " COLOR_BOLD << argInfos->name << COLOR_EOC "  " << \
				argInfos->help << std::endl;
				std::cout << "  " << *argInfos << std::endl;
			}
		}
	}

	// print optional args help
	if (_argsInfos.size() - nbPositional > 0) {
		std::cout << (nbPositional > 0 ? "\n" : "\n\n");
		std::cout << COLOR_ULINE "optional arguments" COLOR_ULINE_R;
		for (auto &&argInfos : _argsInfos) {
			if (!argInfos->required) {
				// if the short option is not available
				if (argInfos->shortName == A_NO_NAME) {
					std::cout << "\n  ";
				}
				else {
					std::cout << "\n  " << COLOR_BOLD "-" << argInfos->shortName << COLOR_EOC;
					if (!argInfos->longName.empty()) {
						std::cout << ", ";
					}
				}
				if (!argInfos->longName.empty()) {
					std::cout << COLOR_BOLD "--" << argInfos->longName << COLOR_EOC;
				}
				std::cout << "  " << argInfos->help << "\n  " << *argInfos << std::endl;
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
		[longName, shortName] (ArgInfo * const &arg) {
			return (arg->shortName != A_NO_NAME && shortName != A_NO_NAME && \
				arg->shortName == shortName) || (!arg->longName.empty() && arg->longName == longName);
		});
	if (nbDuplicates > 0) {
		logErr("duplicate optional arg name: " << "-" << shortName << ", --" << longName);
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}

void	ArgsParser::init() {
	_opts = "uw:g:s:b:";

	_longOpts = {
		{"usage", no_argument, NULL, 'u'},
		{"width", required_argument, NULL, 'w'},
		{"gui", required_argument, NULL, 'g'},
		{"speed", required_argument, NULL, 's'},
		{"boardSize", required_argument, NULL, 0},

		{NULL, 0, NULL, 0}
	};
}

// create new arg of the specified type, add it to _argsInfos, then return a ref
ArgInfo	&ArgsParser::addArgument(std::string name, ArgType::Enum type) {
	ArgInfo	*newElem = nullptr;
	std::pair<std::set<ArgInfo *>::iterator, bool>	elem;

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

	elem = _argsInfos.insert(newElem);

	// check name duplication
	if (!elem.second) {
		logErr("argument name \"" << name << "\" is already taken");
		delete newElem;
		return *(*elem.first);  // return the existing element
	}

	return *(*elem.first);
}


// The variable optind is the index of the next element to be processed in argv.
// The system initializes this value to 1. The caller can reset it to 1 to restart scanning of the same argv,
// or when scanning a new argument vector.

// If the first character of optstring is '+' or the environment variable POSIXLY_CORRECT is set,
// then option processing stops as soon as a nonoption argument is encountered

void	ArgsParser::parseArgs() {
	int	opt;
	int longIndex;

	init();  // init getopt_long args

	std::cout << "parseArgs ----------" << std::endl;

	while ((opt = getopt_long(_ac, _av, _opts.c_str(), _longOpts.data(), &longIndex)) != -1) {
		std::cout << "opt: " << static_cast<char>(opt) << std::endl;
		switch (opt) {
			case 'u': case '?':
				std::cout << "// usage();" << std::endl;
				// usage();
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
			default:
				logErr("parsing args error");
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

