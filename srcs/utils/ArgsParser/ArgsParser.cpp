#include "ArgsParser.hpp"

#include "Logging.hpp"

ArgsParser::ArgsParser() {
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
	std::cout << "need to show usage" << std::endl;
// "usage: ./ft_vox --size-s size [--usage|-u] [--gui|-g guiId] \
// [--moveSpeed|-m moveSpeed] [--boardSize|-b boardSize]
// --usage: display usage of the program
// --width: set the windows width
// --height: set the windows height
// --gui: set the start gui id
// --speed: change the speed
// --boardSize: change the boardSize
// "
}


void	ArgsParser::init() {
	_opts = "uw:h:g:s:b:";

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

void	ArgsParser::parseArgs(int ac, char * const *av) {
	int	opt;
	int longIndex;

	while ((opt = getopt_long(ac, av, _opts.c_str(), _longOpts.data(), &longIndex)) != -1) {
		std::cout << "opt: " << static_cast<char>(opt) << std::endl;
		switch (opt) {
			case 'h': case 'u': case '?':
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
