#include "ArgsParser.hpp"

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
		std::cout << (argInfos->required ? " " : " [");
		std::cout << COLOR_BOLD "-" << argInfos->shortName << COLOR_EOC;

		// if the arg need a value
		if (!(argInfos->type == ArgType::BOOL && reinterpret_cast<BoolArg *>(argInfos)->storeTrue)) {
			std::cout << " " COLOR_ULINE << argInfos->longName << COLOR_ULINE_R;
		}

		if (!argInfos->required) {
			std::cout << "]";
		}
	}

	// print args help
	std::cout << "\n\narguments:" << std::endl;
	for (auto &&argInfos : _argsInfos) {
		std::cout << "  " << COLOR_BOLD "-" << argInfos->shortName << COLOR_EOC ", " \
		COLOR_BOLD "--" << argInfos->longName << COLOR_EOC "  " << argInfos->help << std::endl;
	}
}


void	ArgsParser::init() {
	std::sort(_argsInfos.begin(), _argsInfos.end(), compareArgInfoPtr);

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
ArgInfo	&ArgsParser::addArgument(ArgType::Enum type) {
	if (type == ArgType::BOOL) {
		_argsInfos.push_back(new BoolArg());
	}
	else if (type == ArgType::INT) {
		_argsInfos.push_back(new IntArg());
	}
	else if (type == ArgType::FLOAT) {
		_argsInfos.push_back(new FloatArg());
	}
	else {
		_argsInfos.push_back(new StringArg());
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
