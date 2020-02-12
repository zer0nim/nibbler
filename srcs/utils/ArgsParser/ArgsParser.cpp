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

void	ArgsParser::usage(bool longUsage) const {
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
	std::cout << std::endl;

	if (longUsage) {
		uint32_t	nbPositional = std::count_if(std::begin(_argsInfos), std::end(_argsInfos),
			[] (AInfoArg * const argInfos) {
				return argInfos->getRequired(); });

		// print positional args help
		if (nbPositional > 0) {
			std::cout << COLOR_ULINE "\npositional arguments" COLOR_ULINE_R;
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
			std::cout << COLOR_ULINE "\noptional arguments" COLOR_ULINE_R;
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
			std::cout << COLOR_ULINE "\ndescription" COLOR_ULINE_R << std::endl;
			std::cout << _progDescr << std::endl;
		}
	}
}

// test optionals name validity
bool	ArgsParser::checkOptsAvailability(std::string const &name, std::string const
	&longName, char shortName) {
	std::string const	errInfo = "argument \"" + name + "\": setOptional('" + \
		std::string(1, shortName) + "', \"" + longName + "\"): ";

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

	// short name
	if (shortName != A_NO_NAME) {
		// on duplication
		if (_sOptArgsId.find(shortName) != _sOptArgsId.end()) {
			logErr(errInfo << "short name duplication: " << "-" << shortName);
			return EXIT_FAILURE;
		}
		_sOptArgsId[shortName] = _argsId[name];
	}
	// long name
	if (!longName.empty()) {
		// on duplication
		if (_lOptArgsId.find(longName) != _lOptArgsId.end()) {
			logErr(errInfo << "long name duplication: " << "--" << longName);
			return EXIT_FAILURE;
		}
		_lOptArgsId[longName] = _argsId[name];
	}

	return EXIT_SUCCESS;
}

// create new arg of the specified type, add it to _argsInfos, then return a ref
AInfoArg	&ArgsParser::addArgument(std::string const name, ArgType::Enum type) {
	AInfoArg	*newElem = nullptr;

	// refuse empty name
	if (name.empty()) {
		throw ArgsParserException("addArgument don't accept empty name");
	}

	// create new argument
	newElem = _builders[type](this, name);

	// try to insert the element, fail on name duplicate
	auto elem = _argsId.insert(std::pair<std::string, uint32_t>(name, _argsInfos.size()));

	// on name duplication
	if (!elem.second) {
		logErr("argument name \"" << name << "\" is already taken");
		delete newElem;
		return (*_argsInfos[elem.first->second]);  // return the existing element
	}

	_argsInfos.push_back(newElem);
	return (*_argsInfos.back());  // return the new element
}

// generate getopt_long parameters
void	ArgsParser::_initGetopt() {
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

void	ArgsParser::parseArgs() {
	int	opt;
	int	longIndex = 0;

	uint32_t	nbPositional = std::count_if(std::begin(_argsInfos), std::end(_argsInfos),
		[] (AInfoArg * const argInfos) {
			return argInfos->getRequired(); });
	// nothing has been filled but some positional arguments are needed
	if (nbPositional > 0 && _ac == 1) {
		usage();
		throw ArgsParserException("you need to specify arguments !");
	}

	_initGetopt();  // generate getopt_long parameters

	// manage optionals args
	while ((opt = getopt_long(_ac, _av, _opts.c_str(), _longOpts.data(), &longIndex)) != -1) {
		// show usage and stop
		if (opt == '?' || opt == 'u' || opt == ':') {
			usage(opt == 'u');
			if (opt == 'u') {
				throw ArgsParserUsage();
			}
			else {
				throw ArgsParserException("invalid option");
			}
			break;
		}
		// manage long optional arg
		else if (opt == 0) {
			// with argument
			if (optarg) {
				_argsInfos[_lOptArgsId[_longOpts[longIndex].name]]->setVal(optarg);
			}
			// without argument
			else {
				// the only case where there is no argument is a bool with setStoreTrue,
				_argsInfos[_lOptArgsId[_longOpts[longIndex].name]]->setVal("true");
			}
		}
		// manage short optional arg
		else {
			// with argument
			if (optarg) {  // if the option have argument
				_argsInfos[_sOptArgsId[static_cast<char>(opt)]]->setVal(optarg);
			}
			// without argument
			else {
				// the only case where there is no argument is a bool with setStoreTrue,
				_argsInfos[_sOptArgsId[static_cast<char>(opt)]]->setVal("true");
			}
		}
	}

	// manage positional args
	if (optind < _ac) {
		auto it = _argsInfos.begin();
		bool unused = false;

		// loop through remaining _av args
		while (optind < _ac) {
			unused = false;

			// search the next positional arg
			for (; it != _argsInfos.end(); ++it) {
				if ((*it)->getRequired()) {
					(*it)->setVal(_av[optind]);
					unused = true;
					++it;
					break;
				}
			}

			// too many arguments
			if (!unused) {
				logWarn("argument: \"" << _av[optind] << "\" unused, too many arguments");
			}

			++optind;
		}
		// skip remaining optional argument
		while (it != _argsInfos.end() && !(*it)->getRequired()) { ++it; }

		// user forgot to set some positional arguments
		if (it != _argsInfos.end()) {
			usage();
			throw ArgsParserException("user forgot to set some positional arguments");
		}
	}
}

void	ArgsParser::setProgDescr(std::string const &progDescr) { _progDescr = progDescr; }

// helper function to retrieve an argument by name
AInfoArg	*ArgsParser::_get(std::string const name, ArgType::Enum const type) const {
	auto it = _argsId.find(name);

	// argument `name` not found
	if (it == _argsId.end()) {
		throw ArgsParserException(std::string("argument \"" + name + "\" not found").c_str());
	}

	// invalid type
	if (_argsInfos[it->second]->getType() != type) {
		throw ArgsParserException(std::string("Argument \"" + name +
			"\": types do not match.\nYou ask for an " + ArgType::enumNames[type] +
			", but the arg is of type " + ArgType::enumNames[
			_argsInfos[it->second]->getType()]).c_str());
	}

	return _argsInfos[it->second];
}

// -- exceptions ---------------------------------------------------------------
ArgsParser::ArgsParserException::ArgsParserException()
: std::runtime_error("[ArgsParserError]") {}

ArgsParser::ArgsParserException::ArgsParserException(const char* what_arg)
: std::runtime_error(std::string(std::string("[ArgsParserError] ") + what_arg).c_str()) {}

ArgsParser::ArgsParserUsage::ArgsParserUsage()
: std::runtime_error("[ArgsParserUsage]") {}

// -- statics initialisation ---------------------------------------------------

// used to construct AInfoArg* according to ArgType::Enum
std::array<BuilderFuncPtr, 13> const ArgsParser::_builders = {
	[](ArgsParser *argsParser, std::string const name) -> AInfoArg * {
		return new StringArg(argsParser, name); },  // 									STRING
	[](ArgsParser *argsParser, std::string const name) -> AInfoArg * {
		return new BoolArg(argsParser, name); },  // 									BOOL
	[](ArgsParser *argsParser, std::string const name) -> AInfoArg * {
		return new NumberArg<int8_t>(argsParser, name, ArgType::INT8); },  // 			INT8
	[](ArgsParser *argsParser, std::string const name) -> AInfoArg * {
		return new NumberArg<int16_t>(argsParser, name, ArgType::INT16); },  // 		INT16
	[](ArgsParser *argsParser, std::string const name) -> AInfoArg * {
		return new NumberArg<int32_t>(argsParser, name, ArgType::INT32); },  // 		INT32
	[](ArgsParser *argsParser, std::string const name) -> AInfoArg * {
		return new NumberArg<int64_t>(argsParser, name, ArgType::INT64); },  // 		INT64
	[](ArgsParser *argsParser, std::string const name) -> AInfoArg * {
		return new NumberArg<uint8_t>(argsParser, name, ArgType::UINT8); },  // 		UINT8
	[](ArgsParser *argsParser, std::string const name) -> AInfoArg * {
		return new NumberArg<uint16_t>(argsParser, name, ArgType::UINT16); },  // 		UINT16
	[](ArgsParser *argsParser, std::string const name) -> AInfoArg * {
		return new NumberArg<uint32_t>(argsParser, name, ArgType::UINT32); },  // 		UINT32
	[](ArgsParser *argsParser, std::string const name) -> AInfoArg * {
		return new NumberArg<uint64_t>(argsParser, name, ArgType::UINT64); },  // 		UINT64
	[](ArgsParser *argsParser, std::string const name) -> AInfoArg * {
		return new NumberArg<float_t>(argsParser, name, ArgType::FLOAT); },  // 		FLOAT
	[](ArgsParser *argsParser, std::string const name) -> AInfoArg * {
		return new NumberArg<double>(argsParser, name, ArgType::DOUBLE); },  // 		DOUBLE
	[](ArgsParser *argsParser, std::string const name) -> AInfoArg * {
		return new NumberArg<long double>(argsParser, name, ArgType::L_DOUBLE); },  // L_DOUBLE
};
