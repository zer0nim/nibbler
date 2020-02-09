#include "AInfoArg.hpp"
#include <algorithm>
#include <iomanip>
#include <limits>
#include <locale>

#include "ArgsParser.hpp"

// -- AInfoArg ------------------------------------------------------------------
AInfoArg::AInfoArg()
: _type(ArgType::STRING),
  _name("noName"),
  _shortName(A_NO_NAME),
  _required(true),
  _argsParser(nullptr) {
	  logErr("this constructor should not be called")
}

AInfoArg::AInfoArg(ArgsParser	*argsParser, std::string name, ArgType::Enum type)
: _type(type),
  _name(name),
  _shortName(A_NO_NAME),
  _required(true),
  _argsParser(argsParser) {
}

AInfoArg::~AInfoArg() {
}

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

void AInfoArg::print(std::ostream &out) const {
	out << "<" << COLOR_TYPE << ArgType::enumNames[_type] << COLOR_WHITE;
}

bool	AInfoArg::needArgument() const {
	return (!(_type == ArgType::BOOL && \
		reinterpret_cast<BoolArg const *>(this)->getStoreTrue()));
}

// set optionnals arguments name
AInfoArg	&AInfoArg::setOptional(std::string const &longName, char shortName) {
	// verify option name availability
	if (_argsParser->checkOptsAvailability(_name, longName, shortName) == EXIT_FAILURE) {
		return *this;
	}

	_required = false;  // disable required for optionnals args

	this->_shortName = shortName;
	this->_longName = longName;
	return *this;
}
// idem but allow to set shortName without longName
AInfoArg	&AInfoArg::setOptional(char shortName = A_NO_NAME, std::string const &longName) {
	return setOptional(longName, shortName);
}


AInfoArg	&AInfoArg::setHelp(std::string help) {
	this->_help = help;
	return *this;
}

AInfoArg	&AInfoArg::setDefaultS(std::string defaultV) {
	(void)defaultV;
	logErr("argument of type " << ArgType::enumNames[_type] << " can't use \"setDefaultS\"");
	return *this;
}
AInfoArg	&AInfoArg::setDefaultB(bool defaultV) {
	(void)defaultV;
	logErr("argument of type " << ArgType::enumNames[_type] << " can't use \"setDefaultB\"");
	return *this;
}
AInfoArg	&AInfoArg::setDefaultI32(int32_t defaultV) {
	(void)defaultV;
	logErr("argument of type " << ArgType::enumNames[_type] << " can't use \"setDefaultI32\"");
	return *this;
}
AInfoArg	&AInfoArg::setDefaultI64(int64_t defaultV) {
	(void)defaultV;
	logErr("argument of type " << ArgType::enumNames[_type] << " can't use \"setDefaultI64\"");
	return *this;
}
AInfoArg	&AInfoArg::setDefaultUI32(uint32_t defaultV) {
	(void)defaultV;
	logErr("argument of type " << ArgType::enumNames[_type] << " can't use \"setDefaultUI32\"");
	return *this;
}
AInfoArg	&AInfoArg::setDefaultUI64(uint64_t defaultV) {
	(void)defaultV;
	logErr("argument of type " << ArgType::enumNames[_type] << " can't use \"setDefaultUI64\"");
	return *this;
}
AInfoArg	&AInfoArg::setDefaultF(float defaultV) {
	(void)defaultV;
	logErr("argument of type " << ArgType::enumNames[_type] << " can't use \"setDefaultF\"");
	return *this;
}
AInfoArg	&AInfoArg::setMinI32(int32_t min) {
	(void)min;
	logErr("argument of type " << ArgType::enumNames[_type] << " can't use \"setMinI32\"");
	return *this;
}
AInfoArg	&AInfoArg::setMaxI32(int32_t max) {
	(void)max;
	logErr("argument of type " << ArgType::enumNames[_type] << " can't use \"setMaxI32\"");
	return *this;
}
AInfoArg	&AInfoArg::setMinI64(int64_t min) {
	(void)min;
	logErr("argument of type " << ArgType::enumNames[_type] << " can't use \"setMinI64\"");
	return *this;
}
AInfoArg	&AInfoArg::setMaxI64(int64_t max) {
	(void)max;
	logErr("argument of type " << ArgType::enumNames[_type] << " can't use \"setMaxI64\"");
	return *this;
}
AInfoArg	&AInfoArg::setMinUI32(uint32_t min) {
	(void)min;
	logErr("argument of type " << ArgType::enumNames[_type] << " can't use \"setMinUI32\"");
	return *this;
}
AInfoArg	&AInfoArg::setMaxUI32(uint32_t max) {
	(void)max;
	logErr("argument of type " << ArgType::enumNames[_type] << " can't use \"setMaxUI32\"");
	return *this;
}
AInfoArg	&AInfoArg::setMinUI64(uint64_t min) {
	(void)min;
	logErr("argument of type " << ArgType::enumNames[_type] << " can't use \"setMinUI64\"");
	return *this;
}
AInfoArg	&AInfoArg::setMaxUI64(uint64_t max) {
	(void)max;
	logErr("argument of type " << ArgType::enumNames[_type] << " can't use \"setMaxUI64\"");
	return *this;
}
AInfoArg	&AInfoArg::setMinF(float min) {
	(void)min;
	logErr("argument of type " << ArgType::enumNames[_type] << " can't use \"setMinF\"");
	return *this;
}
AInfoArg	&AInfoArg::setMaxF(float max) {
	(void)max;
	logErr("argument of type " << ArgType::enumNames[_type] << " can't use \"setMaxF\"");
	return *this;
}
AInfoArg	&AInfoArg::setMinLength(uint32_t min) {
	(void)min;
	logErr("argument of type " << ArgType::enumNames[_type] << " can't use \"setMinLength\"");
	return *this;
}
AInfoArg	&AInfoArg::setMaxLength(uint32_t max) {
	(void)max;
	logErr("argument of type " << ArgType::enumNames[_type] << " can't use \"setMaxLength\"");
	return *this;
}
AInfoArg	&AInfoArg::setStoreTrue(bool storeTrue) {
	(void)storeTrue;
	logErr("argument of type " << ArgType::enumNames[_type] << " can't use \"setStoreTrue\"");
	return *this;
}

ArgType::Enum		AInfoArg::getType() const { return _type; }
std::string const	&AInfoArg::getName() const { return _name; }
char				AInfoArg::getShortName() const { return _shortName; }
std::string const	&AInfoArg::getLongName() const { return _longName; }
std::string const	&AInfoArg::getHelp() const { return _help; }
bool				AInfoArg::getRequired() const { return _required; }

std::ostream & operator << (std::ostream &out, AInfoArg const &aInfo) {
	aInfo.print(out);  // delegate the work to the polymorphic member function
	return out;
}

// -- StringArg ----------------------------------------------------------------
StringArg::StringArg(ArgsParser *argsParser, std::string name)
: AInfoArg(argsParser, name, ArgType::STRING),
  _min(0),
  _max(std::numeric_limits<uint32_t>::max()),
  _defaultV({"", false}) {
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
	if (_defaultV.second) {
		out << " " COLOR_L_VAL "default" COLOR_WHITE "=" COLOR_R_VAL "\"" << _defaultV.first << "\"" COLOR_WHITE;
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
	if (defaultV.empty()) {
		logErr("argument \"" << _name << "\": setDefaultS(): default val can't be empty");
	}
	else if (defaultV.size() < _min) {
		logErr("argument \"" << _name << "\": setDefaultS(): default val length(" << defaultV.size() << ") < min:" << _min);
	}
	else if (defaultV.size() > _max) {
		logErr("argument \"" << _name << "\": setDefaultS(): default val length(" << defaultV.size() << ") > max:" << _max);
	}
	else {
		this->_defaultV = {defaultV, true};
		_value = {defaultV, true};  // update _value accordingly
	}
	return *this;
}
AInfoArg	&StringArg::setMinLength(uint32_t min) {
	if (_defaultV.second && min > _defaultV.first.size()) {
		logErr("argument \"" << _name << "\": setMinLength(): min length(" << min << \
			") > default val length(" << _defaultV.first.size() << ")");
	} else {
		this->_min = min;
	}
	return *this;
}
AInfoArg	&StringArg::setMaxLength(uint32_t max) {
	if (_defaultV.second && max < _defaultV.first.size()) {
		logErr("argument \"" << _name << "\": setMaxLength(): max length(" << max << \
			") < default val length(" << _defaultV.first.size() << ")");
	}
	else {
		this->_max = max;
	}
	return *this;
}

uint32_t		StringArg::getMin() const { return _min; }
uint32_t		StringArg::getMax() const { return _max; }
std::pair<std::string, bool>	StringArg::getDefaultV() const { return _defaultV; }
std::pair<std::string, bool>	StringArg::getVal() const { return _value; }

// test the input string and save it
void			StringArg::setVal(std::string input) {
	if (input.empty()) {
		logErr("parseArgs(): argument \"" << _name << "\": input can't be empty");
	}
	else if (input.size() < _min) {
		logErr("parseArgs(): argument \"" << _name << "\": input length(" << input.size() << \
			") < min length(" << _min << ")");
	}
	else if (input.size() > _max) {
		logErr("parseArgs(): argument \"" << _name << "\": input length(" << input.size() << \
			") > max length(" << _max << ")");
	}
	else {
		_value = {input, true};
	}
}
// -- BoolArg ------------------------------------------------------------------
BoolArg::BoolArg(ArgsParser *argsParser, std::string name)
: AInfoArg(argsParser, name, ArgType::BOOL),
  _defaultV(false),
  _storeTrue(false),
  _value({false, true}) {
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
	this->_defaultV = defaultV;
	_value = {defaultV, true};  // update _value accordingly
	return *this;
}
AInfoArg	&BoolArg::setStoreTrue(bool storeTrue) {
	this->_storeTrue = storeTrue;
	return *this;
}

bool	BoolArg::getDefaultV() const { return _defaultV; }
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
		logErr("failed to cast input \"" << input << "\" to bool");
	}
}
// -- Int32Arg -------------------------------------------------------------------
Int32Arg::Int32Arg(ArgsParser *argsParser, std::string name)
: AInfoArg(argsParser, name, ArgType::INT32),
  _min(std::numeric_limits<int32_t>::lowest()),
  _max(std::numeric_limits<int32_t>::max()),
  _defaultV({0, false}),
  _value({0, false}) {
}

Int32Arg::~Int32Arg() {
}

Int32Arg::Int32Arg(Int32Arg const &src): AInfoArg(src) {
	*this = src;
}

Int32Arg &Int32Arg::operator=(Int32Arg const &rhs) {
	AInfoArg::operator=(rhs);
	if (this != &rhs) {
		_min = rhs._min;
		_max = rhs._max;
		_defaultV = rhs._defaultV;
		_value = rhs._value;
	}
	return *this;
}

void Int32Arg::print(std::ostream &out) const {
	AInfoArg::print(out);

	// print defaut int32_t value
	if (_defaultV.second) {
		out << " " COLOR_L_VAL "default" COLOR_WHITE "=" COLOR_R_VAL << _defaultV.first << COLOR_WHITE;
	}

	// print string min/max
	if (_min != std::numeric_limits<int32_t>::lowest() || _max != std::numeric_limits<int32_t>::max()) {
		out << " " COLOR_L_VAL "range" COLOR_WHITE "=" COLOR_R_VAL "[" << \
			(_min != std::numeric_limits<int32_t>::lowest() ? std::to_string(_min) : "") << \
			":" << (_max != std::numeric_limits<int32_t>::max() ? std::to_string(_max) : "") \
			<< "]" COLOR_WHITE;
	}

	out << ">";
}

AInfoArg	&Int32Arg::setDefaultI32(int32_t defaultV) {
	if (defaultV < _min) {
		logErr("argument \"" << _name << "\": setDefaultI32(): default:" << defaultV << " < min:" << _min);
	}
	else if (defaultV > _max) {
		logErr("argument \"" << _name << "\": setDefaultI32(): default:" << defaultV << " > max:" << _max);
	}
	else {
		this->_defaultV = {defaultV, true};
		_value = {defaultV, true};  // update _value accordingly
	}
	return *this;
};
AInfoArg	&Int32Arg::setMinI32(int32_t min) {
	if (_defaultV.second && _defaultV.first < min) {
		logErr("argument \"" << _name << "\": setMinI32(): min:" << min << " > default:" << _defaultV.first);
	}
	else {
		this->_min = min;
	}
	return *this;
};
AInfoArg	&Int32Arg::setMaxI32(int32_t max) {
	if (_defaultV.second && _defaultV.first > max) {
		logErr("argument \"" << _name << "\": setMaxI32(): max:" << max << " < default:" << _defaultV.first);
	}
	else {
		this->_max = max;
	}
	return *this;
};

int32_t	Int32Arg::getMin() const { return _min; }
int32_t	Int32Arg::getMax() const { return _max; };
std::pair<int32_t, bool>	Int32Arg::getDefaultV() const { return _defaultV; }
std::pair<int32_t, bool>	Int32Arg::getVal() const { return _value; }

// convert the input string to int32_t
void	Int32Arg::setVal(std::string input) {
	int64_t	val = 0;
	try {
		val = std::stoi(input);

		if (val < _min) {
			logErr("parseArgs(): argument \"" << _name << "\": out of range, val:" << val << " < min:" << _min);
		}
		else if (val > _max) {
			logErr("parseArgs(): argument \"" << _name << "\": out of range, val:" << val << " > max:" << _max);
		}
		else {
			_value = {val, true};
		}
	}
	catch (const std::out_of_range &e) {
		logErr("parseArgs(): argument \"" << _name << "\": out of range input \"" << input << "\"");
	}
	catch (const std::invalid_argument &e) {
		logErr("parseArgs(): argument \"" << _name << "\": failed to convert input \"" << input << "\"");
	}
}
// -- Int64Arg -------------------------------------------------------------------
Int64Arg::Int64Arg(ArgsParser *argsParser, std::string name)
: AInfoArg(argsParser, name, ArgType::INT64),
  _min(std::numeric_limits<int64_t>::lowest()),
  _max(std::numeric_limits<int64_t>::max()),
  _defaultV({0, false}),
  _value({0, false}) {
}

Int64Arg::~Int64Arg() {
}

Int64Arg::Int64Arg(Int64Arg const &src): AInfoArg(src) {
	*this = src;
}

Int64Arg &Int64Arg::operator=(Int64Arg const &rhs) {
	AInfoArg::operator=(rhs);
	if (this != &rhs) {
		_min = rhs._min;
		_max = rhs._max;
		_defaultV = rhs._defaultV;
		_value = rhs._value;
	}
	return *this;
}

void Int64Arg::print(std::ostream &out) const {
	AInfoArg::print(out);

	// print defaut int64_t value
	if (_defaultV.second) {
		out << " " COLOR_L_VAL "default" COLOR_WHITE "=" COLOR_R_VAL << _defaultV.first << COLOR_WHITE;
	}

	// print string min/max
	if (_min != std::numeric_limits<int64_t>::lowest() || _max != std::numeric_limits<int64_t>::max()) {
		out << " " COLOR_L_VAL "range" COLOR_WHITE "=" COLOR_R_VAL "[" << \
			(_min != std::numeric_limits<int64_t>::lowest() ? std::to_string(_min) : "") << \
			":" << (_max != std::numeric_limits<int64_t>::max() ? std::to_string(_max) : "") \
			<< "]" COLOR_WHITE;
	}

	out << ">";
}

AInfoArg	&Int64Arg::setDefaultI64(int64_t defaultV) {
	if (defaultV < _min) {
		logErr("argument \"" << _name << "\": setDefaultI64(): default:" << defaultV << " < min:" << _min);
	}
	else if (defaultV > _max) {
		logErr("argument \"" << _name << "\": setDefaultI64(): default:" << defaultV << " > max:" << _max);
	}
	else {
		this->_defaultV = {defaultV, true};
		_value = {defaultV, true};  // update _value accordingly
	}
	return *this;
};
AInfoArg	&Int64Arg::setMinI64(int64_t min) {
	if (_defaultV.second && _defaultV.first < min) {
		logErr("argument \"" << _name << "\": setMinI64(): min:" << min << " > default:" << _defaultV.first);
	}
	else {
		this->_min = min;
	}
	return *this;
};
AInfoArg	&Int64Arg::setMaxI64(int64_t max) {
	if (_defaultV.second && _defaultV.first > max) {
		logErr("argument \"" << _name << "\": setMaxI64(): max:" << max << " < default:" << _defaultV.first);
	}
	else {
		this->_max = max;
	}
	return *this;
};

int64_t	Int64Arg::getMin() const { return _min; }
int64_t	Int64Arg::getMax() const { return _max; };
std::pair<int64_t, bool>	Int64Arg::getDefaultV() const { return _defaultV; }
std::pair<int64_t, bool>	Int64Arg::getVal() const { return _value; }


// convert the input string to int64_t
void	Int64Arg::setVal(std::string input) {
	int64_t	val = 0;
	try {
		val = std::stoll(input);

		if (val < _min) {
			logErr("parseArgs(): argument \"" << _name << "\": out of range, val:" << val << " < min:" << _min);
		}
		else if (val > _max) {
			logErr("parseArgs(): argument \"" << _name << "\": out of range, val:" << val << " > max:" << _max);
		}
		else {
			_value = {val, true};
		}
	}
	catch (const std::out_of_range &e) {
		logErr("parseArgs(): argument \"" << _name << "\": out of range input \"" << input << "\"");
	}
	catch (const std::invalid_argument &e) {
		logErr("parseArgs(): argument \"" << _name << "\": failed to convert input \"" << input << "\"");
	}
}
// -- UInt32Arg -------------------------------------------------------------------
UInt32Arg::UInt32Arg(ArgsParser *argsParser, std::string name)
: AInfoArg(argsParser, name, ArgType::UINT32),
  _min(std::numeric_limits<uint32_t>::lowest()),
  _max(std::numeric_limits<uint32_t>::max()),
  _defaultV({0, false}),
  _value({0, false}) {
}

UInt32Arg::~UInt32Arg() {
}

UInt32Arg::UInt32Arg(UInt32Arg const &src): AInfoArg(src) {
	*this = src;
}

UInt32Arg &UInt32Arg::operator=(UInt32Arg const &rhs) {
	AInfoArg::operator=(rhs);
	if (this != &rhs) {
		_min = rhs._min;
		_max = rhs._max;
		_defaultV = rhs._defaultV;
		_value = rhs._value;
	}
	return *this;
}

void UInt32Arg::print(std::ostream &out) const {
	AInfoArg::print(out);

	// print defaut uint32_t value
	if (_defaultV.second) {
		out << " " COLOR_L_VAL "default" COLOR_WHITE "=" COLOR_R_VAL << _defaultV.first << COLOR_WHITE;
	}

	// print string min/max
	if (_min != 0 || _max != std::numeric_limits<uint32_t>::max()) {
		out << " " COLOR_L_VAL "range" COLOR_WHITE "=" COLOR_R_VAL "[" << \
			(_min != 0 ? std::to_string(_min) : "") << \
			":" << (_max != std::numeric_limits<uint32_t>::max() ? std::to_string(_max) : "") \
			<< "]" COLOR_WHITE;
	}

	out << ">";
}

AInfoArg	&UInt32Arg::setDefaultUI32(uint32_t defaultV) {
	if (defaultV < _min) {
		logErr("argument \"" << _name << "\": setDefaultUI32(): default:" << defaultV << " < min:" << _min);
	}
	else if (defaultV > _max) {
		logErr("argument \"" << _name << "\": setDefaultUI32(): default:" << defaultV << " > max:" << _max);
	}
	else {
		this->_defaultV = {defaultV, true};
		_value = {defaultV, true};  // update _value accordingly
	}
	return *this;
};
AInfoArg	&UInt32Arg::setMinUI32(uint32_t min) {
	if (_defaultV.second && _defaultV.first < min) {
		logErr("argument \"" << _name << "\": setMinUI32(): min:" << min << " > default:" << _defaultV.first);
	}
	else {
		this->_min = min;
	}
	return *this;
};
AInfoArg	&UInt32Arg::setMaxUI32(uint32_t max) {
	if (_defaultV.second && _defaultV.first > max) {
		logErr("argument \"" << _name << "\": setMaxUI32(): max:" << max << " < default:" << _defaultV.first);
	}
	else {
		this->_max = max;
	}
	return *this;
};

uint32_t	UInt32Arg::getMin() const { return _min; }
uint32_t	UInt32Arg::getMax() const { return _max; };
std::pair<uint32_t, bool>	UInt32Arg::getDefaultV() const { return _defaultV; }
std::pair<uint32_t, bool>	UInt32Arg::getVal() const { return _value; }

// convert the input string to uint32_t
void		UInt32Arg::setVal(std::string input) {
	uint32_t	val = 0;
	try {
		// cast input to int64_t because std::stoull don't detect out of range
		int64_t	i64Val = std::stoll(input);
		if (i64Val < 0 || i64Val > std::numeric_limits<uint32_t>::max()) {
			throw std::out_of_range("out of range input");
		}
		val = static_cast<uint32_t>(i64Val);

		if (val < _min) {
			logErr("parseArgs(): argument \"" << _name << "\": out of range, val:" << val << " < min:" << _min);
		}
		else if (val > _max) {
			logErr("parseArgs(): argument \"" << _name << "\": out of range, val:" << val << " > max:" << _max);
		}
		else {
			_value = {val, true};
		}
	}
	catch (const std::out_of_range &e) {
		logErr("parseArgs(): argument \"" << _name << "\": out of range input \"" << input << "\"");
	}
	catch (const std::invalid_argument &e) {
		logErr("parseArgs(): argument \"" << _name << "\": failed to convert input \"" << input << "\"");
	}
}
// -- UInt64Arg -------------------------------------------------------------------
UInt64Arg::UInt64Arg(ArgsParser *argsParser, std::string name)
: AInfoArg(argsParser, name, ArgType::UINT64),
  _min(std::numeric_limits<uint64_t>::lowest()),
  _max(std::numeric_limits<uint64_t>::max()),
  _defaultV({0, false}),
  _value({0, false}) {
}

UInt64Arg::~UInt64Arg() {
}

UInt64Arg::UInt64Arg(UInt64Arg const &src): AInfoArg(src) {
	*this = src;
}

UInt64Arg &UInt64Arg::operator=(UInt64Arg const &rhs) {
	AInfoArg::operator=(rhs);
	if (this != &rhs) {
		_min = rhs._min;
		_max = rhs._max;
		_defaultV = rhs._defaultV;
		_value = rhs._value;
	}
	return *this;
}

void UInt64Arg::print(std::ostream &out) const {
	AInfoArg::print(out);

	// print defaut uint64_t value
	if (_defaultV.second) {
		out << " " COLOR_L_VAL "default" COLOR_WHITE "=" COLOR_R_VAL << _defaultV.first << COLOR_WHITE;
	}

	// print string min/max
	if (_min != 0 || _max != std::numeric_limits<uint64_t>::max()) {
		out << " " COLOR_L_VAL "range" COLOR_WHITE "=" COLOR_R_VAL "[" << \
			(_min != 0 ? std::to_string(_min) : "") << \
			":" << (_max != std::numeric_limits<uint64_t>::max() ? std::to_string(_max) : "") \
			<< "]" COLOR_WHITE;
	}

	out << ">";
}

AInfoArg	&UInt64Arg::setDefaultUI64(uint64_t defaultV) {
	if (defaultV < _min) {
		logErr("argument \"" << _name << "\": setDefaultUI64(): default:" << defaultV << " < min:" << _min);
	}
	else if (defaultV > _max) {
		logErr("argument \"" << _name << "\": setDefaultUI64(): default:" << defaultV << " > max:" << _max);
	}
	else {
		this->_defaultV = {defaultV, true};
		_value = {defaultV, true};  // update _value accordingly
	}
	return *this;
};
AInfoArg	&UInt64Arg::setMinUI64(uint64_t min) {
	if (_defaultV.second && _defaultV.first < min) {
		logErr("argument \"" << _name << "\": setMinUI64(): min:" << min << " > default:" << _defaultV.first);
	}
	else {
		this->_min = min;
	}
	return *this;
};
AInfoArg	&UInt64Arg::setMaxUI64(uint64_t max) {
	if (_defaultV.second && _defaultV.first > max) {
		logErr("argument \"" << _name << "\": setMaxUI64(): max:" << max << " < default:" << _defaultV.first);
	}
	else {
		this->_max = max;
	}
	return *this;
};

uint64_t	UInt64Arg::getMin() const { return _min; }
uint64_t	UInt64Arg::getMax() const { return _max; };
std::pair<uint64_t, bool>	UInt64Arg::getDefaultV() const { return _defaultV; }
std::pair<uint64_t, bool>	UInt64Arg::getVal() const { return _value; }

// convert the input string to uint64_t
void		UInt64Arg::setVal(std::string input) {
	uint64_t	val = 0;
	try {
		// first cast input to double to detect out of range
		double	dVal = std::stod(input);
		if (dVal < 0 || dVal > std::numeric_limits<uint64_t>::max()) {
			throw std::out_of_range("out of range input");
		}
		val = std::stoull(input);  // reconvert again for precision

		if (val < _min) {
			logErr("parseArgs(): argument \"" << _name << "\": out of range, val:" << val << " < min:" << _min);
		}
		else if (val > _max) {
			logErr("parseArgs(): argument \"" << _name << "\": out of range, val:" << val << " > max:" << _max);
		}
		else {
			_value = {val, true};
		}
	}
	catch (const std::out_of_range &e) {
		logErr("parseArgs(): argument \"" << _name << "\": out of range input \"" << input << "\"");
	}
	catch (const std::invalid_argument &e) {
		logErr("parseArgs(): argument \"" << _name << "\": failed to convert input \"" << input << "\"");
	}
}
// -- FloatArg -----------------------------------------------------------------
FloatArg::FloatArg(ArgsParser *argsParser, std::string name)
: AInfoArg(argsParser, name, ArgType::FLOAT),
  _min(std::numeric_limits<float>::lowest()),
  _max(std::numeric_limits<float>::max()),
  _defaultV({0.0f, false}),
  _value({0.0f, false}) {
}

FloatArg::~FloatArg() {
}

FloatArg::FloatArg(FloatArg const &src): AInfoArg(src) {
	*this = src;
}

FloatArg &FloatArg::operator=(FloatArg const &rhs) {
	AInfoArg::operator=(rhs);
	if (this != &rhs) {
		_min = rhs._min;
		_max = rhs._max;
		_defaultV = rhs._defaultV;
		_value = rhs._value;
	}
	return *this;
}

void FloatArg::print(std::ostream &out) const {
	AInfoArg::print(out);

	// print defaut int value
	if (_defaultV.second) {
		out << " " COLOR_L_VAL "default" COLOR_WHITE "=" COLOR_R_VAL << _defaultV.first << COLOR_WHITE;
	}

	// print string min/max
	if (_min != std::numeric_limits<float>::lowest() || _max != std::numeric_limits<float>::max()) {
		out << " " COLOR_L_VAL "range" COLOR_WHITE "=" COLOR_R_VAL "[";
		if (_min != std::numeric_limits<float>::lowest()) {
			out << std::fixed << std::setprecision(3) << _min;
		}
		out << ":";
		if (_max != std::numeric_limits<float>::max()) {
			out << std::fixed << std::setprecision(3) << _max;
		}
		out << "]" COLOR_WHITE;
	}

	out << ">";
}

AInfoArg	&FloatArg::setDefaultF(float defaultV) {
	if (defaultV < _min) {
		logErr("argument \"" << _name << "\": setDefaultF(): default:" << defaultV << " < min:" << _min);
	}
	else if (defaultV > _max) {
		logErr("argument \"" << _name << "\": setDefaultF(): default:" << defaultV << " > max:" << _max);
	}
	else {
		this->_defaultV = {defaultV, true};
		_value = {defaultV, true};  // update _value accordingly
	}
	return *this;
};
AInfoArg	&FloatArg::setMinF(float min) {
	if (_defaultV.second && _defaultV.first < min) {
		logErr("argument \"" << _name << "\": setMinF(): min:" << min << " > default:" << _defaultV.first);
	}
	else {
		this->_min = min;
	}
	return *this;
};
AInfoArg	&FloatArg::setMaxF(float max) {
	if (_defaultV.second && _defaultV.first > max) {
		logErr("argument \"" << _name << "\": setMaxF(): max:" << max << " < default:" << _defaultV.first);
	}
	else {
		this->_max = max;
	}
	return *this;
};

float	FloatArg::getMin() const { return _min; }
float	FloatArg::getMax() const { return _max; };
std::pair<float, bool>	FloatArg::getDefaultV() const { return _defaultV; }
std::pair<float, bool>	FloatArg::getVal() const { return _value; }

// convert the input string to float
void	FloatArg::setVal(std::string input) {
	float	val = 0.0f;
	try {
		val = std::stof(input);

		if (val < _min) {
			logErr("parseArgs(): argument \"" << _name << "\": out of range, val:" << val << " < min:" << _min);
		}
		else if (val > _max) {
			logErr("parseArgs(): argument \"" << _name << "\": out of range, val:" << val << " > max:" << _max);
		}
		else {
			_value = {val, true};
		}
	}
	catch (const std::out_of_range &e) {
		logErr("parseArgs(): argument \"" << _name << "\": out of range input \"" << input << "\"");
	}
	catch (const std::invalid_argument &e) {
		logErr("parseArgs(): argument \"" << _name << "\": failed to convert input \"" << input << "\"");
	}
}
// --
