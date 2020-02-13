#include "AInfoArg.hpp"
#include <algorithm>
#include <iomanip>
#include <limits>
#include <locale>

#include "ArgsParser.hpp"

// -----------------------------------------------------------------------------
// -- AInfoArg -----------------------------------------------------------------
AInfoArg::AInfoArg(ArgsParser *argsParser, std::string const &name, ArgType::Enum type,
	std::string const &longName, char shortName)
: _type(type),
  _name(name),
  _shortName(A_NO_NAME),
  _required(true),
  _argsParser(argsParser) {
	// if the arg is optionnal
	if (!longName.empty() || shortName != A_NO_NAME) {
		// verify option name availability
		_argsParser->checkOptsAvailability(_name, longName, shortName);

		_required = false;
		this->_shortName = shortName;
		this->_longName = longName;
	}
}

AInfoArg::~AInfoArg() {}

AInfoArg::AInfoArg(AInfoArg const &src) {
	*this = src;
}

AInfoArg &AInfoArg::operator=(AInfoArg const &rhs) {
	if (this != &rhs) {
		_type = rhs._type;
		_name = rhs._name;
		_shortName = rhs._shortName;
		_longName = rhs._longName;
		_help = rhs._help;
		_required = rhs._required;
	}
	return *this;
}

AInfoArg	&AInfoArg::setHelp(std::string help) {
	this->_help = help;
	return *this;
}

// -- unknown function ---------------------------------------------------------
void		AInfoArg::unknownFunction(std::string const &funcName) {
	throw AInfoArgError(std::string("argument of type " + ArgType::enumNames[_type]
		+ " can't use \"" + funcName + '"').c_str());
}
AInfoArg	&AInfoArg::setDefaultS(std::string defaultV) {
	(void)defaultV;
	unknownFunction("setDefaultS");
	return *this;
}
AInfoArg	&AInfoArg::setDefaultB(bool defaultV) {
	(void)defaultV;
	unknownFunction("setDefaultB");
	return *this;
}
AInfoArg	&AInfoArg::setDefaultF(long double defaultV) {
	(void)defaultV;
	unknownFunction("setDefaultF");
	return *this;
}
AInfoArg	&AInfoArg::setMinF(long double min) {
	(void)min;
	unknownFunction("setMinF");
	return *this;
}
AInfoArg	&AInfoArg::setMaxF(long double max) {
	(void)max;
	unknownFunction("setMaxF");
	return *this;
}
AInfoArg	&AInfoArg::setDefaultI(int64_t defaultV) {
	(void)defaultV;
	unknownFunction("setDefaultI");
	return *this;
}
AInfoArg	&AInfoArg::setMinI(int64_t min) {
	(void)min;
	unknownFunction("setMinI");
	return *this;
}
AInfoArg	&AInfoArg::setMaxI(int64_t max) {
	(void)max;
	unknownFunction("setMaxI");
	return *this;
}
AInfoArg	&AInfoArg::setDefaultU(uint64_t defaultV) {
	(void)defaultV;
	unknownFunction("setDefaultU");
	return *this;
}
AInfoArg	&AInfoArg::setMinU(uint64_t min) {
	(void)min;
	unknownFunction("setMinU");
	return *this;
}
AInfoArg	&AInfoArg::setMaxU(uint64_t max) {
	(void)max;
	unknownFunction("setMaxU");
	return *this;
}
AInfoArg	&AInfoArg::setStoreTrue(bool storeTrue) {
	(void)storeTrue;
	unknownFunction("setStoreTrue");
	return *this;
}

// print argument type, (overloaded by children)
void AInfoArg::print(std::ostream &out) const {
	out << "<" << COLOR_TYPE << ArgType::enumNames[_type] << COLOR_WHITE;
}

std::ostream & operator << (std::ostream &out, AInfoArg const &aInfo) {
	aInfo.print(out);  // delegate the work to the polymorphic member function
	return out;
}

// -- getters ------------------------------------------------------------------
bool				AInfoArg::needArgument() const {
	return (!(_type == ArgType::BOOL && \
		reinterpret_cast<BoolArg const *>(this)->getStoreTrue()));
}
ArgType::Enum		AInfoArg::getType() const { return _type; }
std::string const	&AInfoArg::getName() const { return _name; }
char				AInfoArg::getShortName() const { return _shortName; }
std::string const	&AInfoArg::getLongName() const { return _longName; }
std::string const	&AInfoArg::getHelp() const { return _help; }
bool				AInfoArg::getRequired() const { return _required; }

// -- exceptions ---------------------------------------------------------------
AInfoArg::AInfoArgError::AInfoArgError()
: std::runtime_error("") {}

AInfoArg::AInfoArgError::AInfoArgError(const char* what_arg)
: std::runtime_error(what_arg) {}

// -----------------------------------------------------------------------------
// -- StringArg ----------------------------------------------------------------
StringArg::StringArg(ArgsParser *argsParser, std::string const &name, std::string const &longName,
	char shortName)
: AInfoArg(argsParser, name, ArgType::STRING, longName, shortName),
  _min(0),
  _max(std::numeric_limits<uint32_t>::max()) {
	// if positionnal argument
	if (!_required) {
		_value.second = true;  // enable default value
	}
}

StringArg::~StringArg() {
}

StringArg::StringArg(StringArg const &src): AInfoArg(src) {
	*this = src;
}

StringArg &StringArg::operator=(StringArg const &rhs) {
	AInfoArg::operator=(rhs);
	if (this != &rhs) {
		_min = rhs._min;
		_max = rhs._max;
		_defaultV = rhs._defaultV;
		_value = rhs._value;
	}
	return *this;
}

void StringArg::print(std::ostream &out) const {
	AInfoArg::print(out);

	// print defaut string value
	if (!_required) {
		out << " " COLOR_L_VAL "default" COLOR_WHITE "=" COLOR_R_VAL "\"" <<
			_defaultV << "\"" COLOR_WHITE;
	}

	// print string min/max
	if (_min != 0 || _max != std::numeric_limits<uint32_t>::max()) {
		out << " " COLOR_L_VAL "length" COLOR_WHITE "=" COLOR_R_VAL "[" << \
		(_min != 0 ? std::to_string(_min) : "") << ":" << \
		(_max != std::numeric_limits<uint32_t>::max() ? std::to_string(_max) : "") \
		<< "]" COLOR_WHITE;
	}

	out << ">";
}

AInfoArg	&StringArg::setDefaultS(std::string defaultV) {
	if (_required) {
		throw AInfoArgError(std::string("arg \"" + _name + "\": setDefaultS(): "
		"you can't set default value of positional arguments").c_str());
	}
	else if (defaultV.size() < _min) {
		throw AInfoArgError(std::string("argument \"" + _name +
			"\": setDefaultS(): default val length(" + std::to_string(defaultV.size())
			+ ") < min:" + std::to_string(_min)).c_str());
	}
	else if (defaultV.size() > _max) {
		throw AInfoArgError(std::string("argument \"" + _name +
			"\": setDefaultS(): default val length(" + std::to_string(defaultV.size())
			+ ") > max:" + std::to_string(_max)).c_str());
	}
	else {
		this->_defaultV = defaultV;
		_value = {defaultV, true};  // update _value accordingly
	}
	return *this;
}
AInfoArg	&StringArg::setMinU(uint64_t min) {
	if (!_required && min > _defaultV.size()) {
		throw AInfoArgError(std::string("argument \"" + _name +
			"\": setMin(): min length(" + std::to_string(min) +
			") > default val length(" + std::to_string(_defaultV.size()) + ")").c_str());
	} else {
		this->_min = min;
	}
	return *this;
}
AInfoArg	&StringArg::setMaxU(uint64_t max) {
	if (!_required && max < _defaultV.size()) {
		throw AInfoArgError(std::string("argument \"" + _name +
			"\": setMax(): max length(" + std::to_string(max) + ") < default val length("
			+ std::to_string(_defaultV.size()) + ")").c_str());
	}
	else {
		this->_max = max;
	}
	return *this;
}

uint32_t		StringArg::getMin() const { return _min; }
uint32_t		StringArg::getMax() const { return _max; }
std::pair<std::string, bool>	StringArg::getVal() const { return _value; }

// test the input string and save it
void			StringArg::setVal(std::string input) {
	if (input.empty()) {
		throw AInfoArgError(std::string("parseArgs(): argument \"" + _name +
			"\": input can't be empty").c_str());
	}
	else if (input.size() < _min) {
		throw AInfoArgError(std::string("parseArgs(): argument \"" + _name +
			"\": input length(" + std::to_string(input.size()) + ") < min length("
			+ std::to_string(_min) + ")").c_str());
	}
	else if (input.size() > _max) {
		throw AInfoArgError(std::string("parseArgs(): argument \"" + _name +
			"\": input length(" + std::to_string(input.size()) + ") > max length("
			+ std::to_string(_max) + ")").c_str());
	}
	else {
		_value = {input, true};
	}
}

// -----------------------------------------------------------------------------
// -- BoolArg ------------------------------------------------------------------
BoolArg::BoolArg(ArgsParser *argsParser, std::string const &name, std::string const &longName,
	char shortName)
: AInfoArg(argsParser, name, ArgType::BOOL, longName, shortName),
  _defaultV(false),
  _storeTrue(false),
  _value({false, true}) {
	// if positionnal argument
	if (!_required) {
		_value.second = true;  // enable default value
	}
}

BoolArg::~BoolArg() {
}

BoolArg::BoolArg(BoolArg const &src): AInfoArg(src) {
	*this = src;
}

BoolArg &BoolArg::operator=(BoolArg const &rhs) {
	AInfoArg::operator=(rhs);
	if (this != &rhs) {
		_defaultV = rhs._defaultV;
		_storeTrue = rhs._storeTrue;
		_value = rhs._value;
	}
	return *this;
}

void BoolArg::print(std::ostream &out) const {
	AInfoArg::print(out);

	// print defaut string value
	out << " " COLOR_L_VAL "default" COLOR_WHITE "=" COLOR_R_VAL << std::boolalpha << _defaultV << COLOR_WHITE;

	if (_storeTrue) {
		out << " " COLOR_L_VAL "storeTrue" COLOR_WHITE;
	}

	out << ">";
}

AInfoArg	&BoolArg::setDefaultB(bool defaultV) {
	if (_required) {
		throw AInfoArgError(std::string("arg \"" + _name + "\": setDefaultB(): "
		"you can't set default value of positional arguments").c_str());
	}
	this->_defaultV = defaultV;
	_value = {defaultV, true};  // update _value accordingly
	return *this;
}
AInfoArg	&BoolArg::setStoreTrue(bool storeTrue) {
	this->_storeTrue = storeTrue;
	return *this;
}

bool	BoolArg::getStoreTrue() const { return _storeTrue; }
std::pair<bool, bool>	BoolArg::getVal() const { return _value; }

// trim whitespace from begin/en of a string
std::string	trimS(std::string const &str) {
	std::string	whitespace = " \t\v\r\n";

	std::size_t start = str.find_first_not_of(whitespace);
	// if no characters are found
	if (start == std::string::npos) {
		return std::string();
	}
	std::size_t end = str.find_last_not_of(whitespace);

	return str.substr(start, end - start + 1);
}

// convert the input string to bool
void	BoolArg::setVal(std::string input) {
	std::array<std::string, 3> trueStr = {"true", "t", "1"};
	std::array<std::string, 3> falseStr = {"false", "f", "0"};

	std::string lowInput = trimS(input);
	// transform the string to lowercase
	std::transform(lowInput.begin(), lowInput.end(), lowInput.begin(), ::tolower);

	// compare lowInput with valid true string
	if (std::any_of(trueStr.begin(), trueStr.end(),
		[lowInput] (std::string const str) { return str == lowInput; })) {
		_value = {true, true};
	}
	// compare lowInput with valid false string
	else if (std::any_of(falseStr.begin(), falseStr.end(),
		[lowInput] (std::string const str) { return str == lowInput; })) {
		_value = {false, true};
	}
	else {
		throw AInfoArgError(std::string("failed to cast input \"" + input +
			"\" to bool").c_str());
	}
}
