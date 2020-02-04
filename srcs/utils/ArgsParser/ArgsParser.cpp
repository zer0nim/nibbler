#include "ArgsParser.hpp"

#include <algorithm>

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
		std::cout << COLOR_ULINE "\n\npositional arguments:" COLOR_ULINE_R;
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
		std::cout << (nbPositional > 0 ? "\n" : "\n\n") << COLOR_ULINE "optional arguments:" COLOR_ULINE_R;
		for (auto &&argInfos : _argsInfos) {
			if (!argInfos->required) {
				// if the short option is not available
				if (argInfos->shortName == A_NO_NAME) {
					std::cout << "\n  ";
				}
				else {
					std::cout << "\n  " << COLOR_BOLD "-" << argInfos->shortName << COLOR_EOC ", ";
				}
				std::cout << COLOR_BOLD "--" << argInfos->longName << COLOR_EOC "  " \
				<< argInfos->help << std::endl;
				std::cout << "  " << *argInfos << std::endl;
			}
		}
	}
}


void	ArgsParser::init() {
	_opts = "uwgsb";

	_longOpts = {
		{"usage", no_argument, NULL, 'u'},
		{"width", required_argument, NULL, 'w'},
		{"gui", required_argument, NULL, 'g'},
		{"speed", required_argument, NULL, 's'},
		{"boardSize", required_argument, NULL, 'b'},

		{NULL, 0, NULL, 0}
	};
}

// create new arg of the specified type, add it to _argsInfos, then return a ref
ArgInfo	&ArgsParser::addArgument(std::string name, ArgType::Enum type) {
	if (type == ArgType::BOOL) {
		_argsInfos.push_back(new BoolArg(name));
	}
	else if (type == ArgType::INT32) {
		_argsInfos.push_back(new Int32Arg(name));
	}
	else if (type == ArgType::INT64) {
		_argsInfos.push_back(new Int64Arg(name));
	}
	else if (type == ArgType::UINT32) {
		_argsInfos.push_back(new UInt32Arg(name));
	}
	else if (type == ArgType::INT64) {
		_argsInfos.push_back(new UInt64Arg(name));
	}
	else if (type == ArgType::FLOAT) {
		_argsInfos.push_back(new FloatArg(name));
	}
	else {
		_argsInfos.push_back(new StringArg(name));
	}

	return *_argsInfos.back();
}

void	ArgsParser::parseArgs() {
	int	opt;
	int longIndex;

	std::cout << "parseArgs ----------" << std::endl;

	while ((opt = getopt_long(_ac, _av, _opts.c_str(), _longOpts.data(), &longIndex)) != -1) {
		std::cout << "opt: " << static_cast<char>(opt) << std::endl;
		switch (opt) {
			case 'u': case '?':
				usage();
				break;
			case 'w':
				break;
			case 'g':
				break;
			case 's':
				break;
			case 'b':
				break;
			default:
				logErr("parsing args error");
			break;
		}
	}
}
