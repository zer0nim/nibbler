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
			std::cout << " " LOG_COL_ULINE << argInfos->getName() << LOG_COL_EOC;
		}
		// print optional arguments
		if (!argInfos->getRequired()) {
			if (argInfos->getShortName() == A_NO_NAME) {
				std::cout << " [" LOG_COL_BOLD "--" << argInfos->getLongName() << LOG_COL_EOC;
			}
			else {
				std::cout << " [" LOG_COL_BOLD "-" << argInfos->getShortName() << LOG_COL_EOC;
			}

			if (argInfos->needArgument()) {
				std::cout << " " LOG_COL_ULINE << argInfos->getName() << LOG_COL_ULINE_R;
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
			std::cout << LOG_COL_ULINE "\npositional arguments" LOG_COL_ULINE_R;
			for (auto &&argInfos : _argsInfos) {
				if (argInfos->getRequired()) {
					std::cout << "\n  " LOG_COL_ULINE << argInfos->getName() << LOG_COL_EOC ":  " << \
					argInfos->getHelp() << std::endl;
					std::cout << "  " << *argInfos << std::endl;
				}
			}
		}

		// print optional args help
		if (_argsInfos.size() - nbPositional > 0) {
			std::cout << LOG_COL_ULINE "\noptional arguments" LOG_COL_ULINE_R;
			for (auto &&argInfos : _argsInfos) {
				if (!argInfos->getRequired()) {
					std::cout << "\n  " LOG_COL_ULINE << argInfos->getName() << LOG_COL_EOC ":  ";

					// if the short name is available
					if (argInfos->getShortName() != A_NO_NAME) {
						std::cout << LOG_COL_BOLD "-" << argInfos->getShortName() << LOG_COL_EOC;
						if (!argInfos->getLongName().empty()) {
							std::cout << ", ";
						}
					}
					if (!argInfos->getLongName().empty()) {
						std::cout << LOG_COL_BOLD "--" << argInfos->getLongName() << LOG_COL_EOC;
					}
					std::cout << "  " << argInfos->getHelp() << "\n  " << *argInfos << std::endl;
				}
			}
		}

		// print program description
		if (!_progDescr.empty()) {
			std::cout << LOG_COL_ULINE "\ndescription" LOG_COL_ULINE_R << std::endl;
			std::cout << "  " << _progDescr << std::endl;
		}
	}
}

// test optionals name validity
void	ArgsParser::checkOptsAvailability(std::string const &name, std::string const &longName,
	char shortName) {
	std::string const	errInfo = "arg \"" + name + "\": addArgument(..., \"" + \
		longName + "\", '" + std::string(1, shortName) + "'): ";

	// shortName invalid char
	if (!isalnum(shortName) && shortName != A_NO_NAME) {
		throw ArgsParserException(std::string(errInfo +
			"shortName only accept alphanumeric chars").c_str());
	}

	// accept only alphanumeric and '-' '_' chars
	auto isInvalidChar = [](char c) {
		return !(isalnum(c) || c == ' ' || c == '-' || c == '_'); };
	// longName invalid char
	if (!longName.empty() && find_if(longName.begin(), longName.end(), isInvalidChar)
		!= longName.end()) {
		throw ArgsParserException(std::string(errInfo +
			"longName only accept alphanumeric, '-' and '_' chars").c_str());
	}

	// refuse char '-' at the begining of a long/short name
	if (shortName == '-' || longName[0] == '-') {
		throw ArgsParserException(std::string(errInfo +
			"you can't put char '-' at the begining of a long/short name").c_str());
	}

	// The -W option is reserved by POSIX.2 for implementation extensions
	if (shortName == 'W') {
		throw ArgsParserException(std::string(errInfo +
			"the -W option is reserved by POSIX.2 for implementation extensions").c_str());
	}

	// The -u option is reserved for usage
	if (shortName == 'u') {
		throw ArgsParserException(std::string(errInfo +
			"The -u short option is reserved for usage").c_str());
	}

	// The -u option is reserved for usage
	if (longName == "usage") {
		throw ArgsParserException(std::string(errInfo +
			"The --usage long option is reserved for usage").c_str());
	}

	// short name
	if (shortName != A_NO_NAME) {
		// on duplication
		if (_sOptArgsId.find(shortName) != _sOptArgsId.end()) {
			throw ArgsParserException(std::string(errInfo +
				"short name duplication: -" + shortName).c_str());
		}
		_sOptArgsId[shortName] = _argsId[name];
	}
	// long name
	if (!longName.empty()) {
		// on duplication
		if (_lOptArgsId.find(longName) != _lOptArgsId.end()) {
			throw ArgsParserException(std::string(errInfo +
				"long name duplication: --" + longName).c_str());
		}
		_lOptArgsId[longName] = _argsId[name];
	}
}

// create new arg of the specified type, add it to _argsInfos, then return a ref
AInfoArg	&ArgsParser::addArgument(std::string const name, ArgType::Enum const type,
	std::string const longName, char shortName) {
	// refuse empty name
	if (name.empty()) {
		throw ArgsParserException("addArgument don't accept empty name");
	}

	// try to insert the element, fail on name duplicate
	auto elem = _argsId.insert(std::pair<std::string, uint32_t>(name, _argsInfos.size()));

	// on name duplication
	if (!elem.second) {
		throw ArgsParserException(std::string("argument name \"" + name +
			"\" is already taken").c_str());
		return (*_argsInfos[elem.first->second]);  // return the existing element
	}

	// create and add new argument
	_argsInfos.push_back(_builders[type](this, name, longName, shortName));
	return (*_argsInfos.back());  // return the new element
}
AInfoArg	&ArgsParser::addArgument(std::string const name, ArgType::Enum const type) {
	return addArgument(name, type, std::string());
}
AInfoArg	&ArgsParser::addArgument(std::string const name, ArgType::Enum const type,
	char shortName, std::string const longName) {
	return addArgument(name, type, longName, shortName);
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

void	ArgsParser::_strReplace(std::string &str, std::string search, std::string replace) {
	size_t it = str.find(search);

	while (it != std::string::npos) {
		str.replace(it, search.size(), replace);
		it = str.find(search, it + replace.size());
	}
}

void	ArgsParser::setProgDescr(std::string const &progDescr) {
	_progDescr = progDescr;
	_strReplace(_progDescr, "\n", "\n  ");
}

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
	[](ArgsParser *argsParser, std::string const &name, std::string const &longName, char shortName)
		-> AInfoArg * {  // STRING
			return new StringArg(argsParser, name, longName, shortName); },
	[](ArgsParser *argsParser, std::string const &name, std::string const &longName, char shortName)
		-> AInfoArg * {  // BOOL
			 return new BoolArg(argsParser, name, longName, shortName); },
	[](ArgsParser *argsParser, std::string const &name, std::string const &longName, char shortName)
		-> AInfoArg * {  // INT8
			 return new NumberArg<int8_t>(argsParser, name, ArgType::INT8, longName, shortName); },
	[](ArgsParser *argsParser, std::string const &name, std::string const &longName, char shortName)
		-> AInfoArg * {  // INT16
			 return new NumberArg<int16_t>(argsParser, name, ArgType::INT16, longName, shortName); },
	[](ArgsParser *argsParser, std::string const &name, std::string const &longName, char shortName)
		-> AInfoArg * {  // INT32
			 return new NumberArg<int32_t>(argsParser, name, ArgType::INT32, longName, shortName); },
	[](ArgsParser *argsParser, std::string const &name, std::string const &longName, char shortName)
		-> AInfoArg * {  // INT64
			 return new NumberArg<int64_t>(argsParser, name, ArgType::INT64, longName, shortName); },
	[](ArgsParser *argsParser, std::string const &name, std::string const &longName, char shortName)
		-> AInfoArg * {  // UINT8
			 return new NumberArg<uint8_t>(argsParser, name, ArgType::UINT8, longName, shortName); },
	[](ArgsParser *argsParser, std::string const &name, std::string const &longName, char shortName)
		-> AInfoArg * {  // UINT16
			 return new NumberArg<uint16_t>(argsParser, name, ArgType::UINT16, longName, shortName); },
	[](ArgsParser *argsParser, std::string const &name, std::string const &longName, char shortName)
		-> AInfoArg * {  // UINT32
			 return new NumberArg<uint32_t>(argsParser, name, ArgType::UINT32, longName, shortName); },
	[](ArgsParser *argsParser, std::string const &name, std::string const &longName, char shortName)
		-> AInfoArg * {  // UINT64
			 return new NumberArg<uint64_t>(argsParser, name, ArgType::UINT64, longName, shortName); },
	[](ArgsParser *argsParser, std::string const &name, std::string const &longName, char shortName)
		-> AInfoArg * {  // FLOAT
			 return new NumberArg<float_t>(argsParser, name, ArgType::FLOAT, longName, shortName); },
	[](ArgsParser *argsParser, std::string const &name, std::string const &longName, char shortName)
		-> AInfoArg * {  // DOUBLE
			 return new NumberArg<double>(argsParser, name, ArgType::DOUBLE, longName, shortName); },
	[](ArgsParser *argsParser, std::string const &name, std::string const &longName, char shortName)
		-> AInfoArg * {  // L_DOUBLE
			 return new NumberArg<long double>(argsParser, name, ArgType::L_DOUBLE, longName, shortName); },
};
