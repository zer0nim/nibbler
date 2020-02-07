#include "AInfoArg.hpp"
#include <limits>
#include <iomanip>

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
	if (_argsParser->checkOptsAvailability(longName, shortName) == EXIT_FAILURE) {
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
	logErr("[" << ArgType::enumNames[_type] << "] unknow setDefaultS function");
	return *this;
}
AInfoArg	&AInfoArg::setDefaultB(bool defaultV) {
	(void)defaultV;
	logErr("[" << ArgType::enumNames[_type] << "] unknow setDefaultB function");
	return *this;
}
AInfoArg	&AInfoArg::setDefaultI32(int32_t defaultV) {
	(void)defaultV;
	logErr("[" << ArgType::enumNames[_type] << "] unknow setDefaultI32 function");
	return *this;
}
AInfoArg	&AInfoArg::setDefaultI64(int64_t defaultV) {
	(void)defaultV;
	logErr("[" << ArgType::enumNames[_type] << "] unknow setDefaultI64 function");
	return *this;
}
AInfoArg	&AInfoArg::setDefaultUI32(uint32_t defaultV) {
	(void)defaultV;
	logErr("[" << ArgType::enumNames[_type] << "] unknow setDefaultUI32 function");
	return *this;
}
AInfoArg	&AInfoArg::setDefaultUI64(uint64_t defaultV) {
	(void)defaultV;
	logErr("[" << ArgType::enumNames[_type] << "] unknow setDefaultUI64 function");
	return *this;
}
AInfoArg	&AInfoArg::setDefaultF(float defaultV) {
	(void)defaultV;
	logErr("[" << ArgType::enumNames[_type] << "] unknow setDefaultF function");
	return *this;
}
AInfoArg	&AInfoArg::setMinI32(int32_t min) {
	(void)min;
	logErr("[" << ArgType::enumNames[_type] << "] unknow setMinI32 function");
	return *this;
}
AInfoArg	&AInfoArg::setMaxI32(int32_t max) {
	(void)max;
	logErr("[" << ArgType::enumNames[_type] << "] unknow setMaxI32 function");
	return *this;
}
AInfoArg	&AInfoArg::setMinI64(int64_t min) {
	(void)min;
	logErr("[" << ArgType::enumNames[_type] << "] unknow setMinI64 function");
	return *this;
}
AInfoArg	&AInfoArg::setMaxI64(int64_t max) {
	(void)max;
	logErr("[" << ArgType::enumNames[_type] << "] unknow setMaxI64 function");
	return *this;
}
AInfoArg	&AInfoArg::setMinUI32(uint32_t min) {
	(void)min;
	logErr("[" << ArgType::enumNames[_type] << "] unknow setMinUI32 function");
	return *this;
}
AInfoArg	&AInfoArg::setMaxUI32(uint32_t max) {
	(void)max;
	logErr("[" << ArgType::enumNames[_type] << "] unknow setMaxUI32 function");
	return *this;
}
AInfoArg	&AInfoArg::setMinUI64(uint64_t min) {
	(void)min;
	logErr("[" << ArgType::enumNames[_type] << "] unknow setMinUI64 function");
	return *this;
}
AInfoArg	&AInfoArg::setMaxUI64(uint64_t max) {
	(void)max;
	logErr("[" << ArgType::enumNames[_type] << "] unknow setMaxUI64 function");
	return *this;
}
AInfoArg	&AInfoArg::setMinF(float min) {
	(void)min;
	logErr("[" << ArgType::enumNames[_type] << "] unknow setMinF function");
	return *this;
}
AInfoArg	&AInfoArg::setMaxF(float max) {
	(void)max;
	logErr("[" << ArgType::enumNames[_type] << "] unknow setMaxF function");
	return *this;
}
AInfoArg	&AInfoArg::setMinLength(uint32_t min) {
	(void)min;
	logErr("[" << ArgType::enumNames[_type] << "] unknow setMinLength function");
	return *this;
}
AInfoArg	&AInfoArg::setMaxLength(uint32_t max) {
	(void)max;
	logErr("[" << ArgType::enumNames[_type] << "] unknow setMaxLength function");
	return *this;
}
AInfoArg	&AInfoArg::setStoreTrue(bool storeTrue) {
	(void)storeTrue;
	logErr("[" << ArgType::enumNames[_type] << "] unknow setStoreTrue function");
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
  _max(std::numeric_limits<uint32_t>::max()) {
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
	if (!_defaultV.empty()) {
		out << " " COLOR_L_VAL "default" COLOR_WHITE "=" COLOR_R_VAL "\"" << _defaultV << "\"" COLOR_WHITE;
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
	if (defaultV.size() < _min) {
		logWarn("your default string length is lesser than the minimal length");
	}
	else if (defaultV.size() > _max) {
		logWarn("your default string length is bigger than the maximal length");
	}
	this->_defaultV = defaultV;
	_value = {defaultV, true};  // update _value accordingly
	return *this;
}
AInfoArg	&StringArg::setMinLength(uint32_t min) {
	if (min > _defaultV.size()) {
		logWarn("your minimal length is bigger than the default string length");
	}
	this->_min = min;
	return *this;
}
AInfoArg	&StringArg::setMaxLength(uint32_t max) {
	if (max < _defaultV.size()) {
		logWarn("your maximal length is lesser than the default string length");
	}
	this->_max = max;
	return *this;
}

uint32_t		StringArg::getMin() const { return _min; }
uint32_t		StringArg::getMax() const { return _max; }
std::string		StringArg::getDefaultV() const { return _defaultV; }
std::pair<std::string, bool>	StringArg::getVal() const { return _value; }
void			StringArg::setVal(std::string strVal) {
	_value = {strVal, true};
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
void	BoolArg::setVal(std::string strVal) {
	(void)strVal;
	_value = {false, true};
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
		logWarn("you have set a default value lesser than the minimal value");
	}
	else if (defaultV > _max) {
		logWarn("you have set a default value bigger than the maximal value");
	}
	this->_defaultV = {defaultV, true};
	_value = {defaultV, true};  // update _value accordingly
	return *this;
};
AInfoArg	&Int32Arg::setMinI32(int32_t min) {
	if (_defaultV.second && _defaultV.first < min) {
		logWarn("you have set a minimal value bigger than the default value");
	}
	this->_min = min;
	return *this;
};
AInfoArg	&Int32Arg::setMaxI32(int32_t max) {
	if (_defaultV.second && _defaultV.first > max) {
		logWarn("you have set a maximal value lesser than the default value");
	}
	this->_max = max;
	return *this;
};

int32_t	Int32Arg::getMin() const { return _min; }
int32_t	Int32Arg::getMax() const { return _max; };
std::pair<int32_t, bool>	Int32Arg::getDefaultV() const { return _defaultV; }
std::pair<int32_t, bool>	Int32Arg::getVal() const { return _value; }
void	Int32Arg::setVal(std::string strVal) {
	(void)strVal;
	_value = {42, true};
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
		logWarn("you have set a default value lesser than the minimal value");
	}
	else if (defaultV > _max) {
		logWarn("you have set a default value bigger than the maximal value");
	}
	this->_defaultV = {defaultV, true};
	_value = {defaultV, true};  // update _value accordingly
	return *this;
};
AInfoArg	&Int64Arg::setMinI64(int64_t min) {
	if (_defaultV.second && _defaultV.first < min) {
		logWarn("you have set a minimal value bigger than the default value");
	}
	this->_min = min;
	return *this;
};
AInfoArg	&Int64Arg::setMaxI64(int64_t max) {
	if (_defaultV.second && _defaultV.first > max) {
		logWarn("you have set a maximal value lesser than the default value");
	}
	this->_max = max;
	return *this;
};

int64_t	Int64Arg::getMin() const { return _min; }
int64_t	Int64Arg::getMax() const { return _max; };
std::pair<int64_t, bool>	Int64Arg::getDefaultV() const { return _defaultV; }
std::pair<int64_t, bool>	Int64Arg::getVal() const { return _value; }
void	Int64Arg::setVal(std::string strVal) {
	(void)strVal;
	_value = {42, true};
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
		logWarn("you have set a default value lesser than the minimal value");
	}
	else if (defaultV > _max) {
		logWarn("you have set a default value bigger than the maximal value");
	}
	this->_defaultV = {defaultV, true};
	_value = {defaultV, true};  // update _value accordingly
	return *this;
};
AInfoArg	&UInt32Arg::setMinUI32(uint32_t min) {
	if (_defaultV.second && _defaultV.first < min) {
		logWarn("you have set a minimal value bigger than the default value");
	}
	this->_min = min;
	return *this;
};
AInfoArg	&UInt32Arg::setMaxUI32(uint32_t max) {
	if (_defaultV.second && _defaultV.first > max) {
		logWarn("you have set a maximal value lesser than the default value");
	}
	this->_max = max;
	return *this;
};

uint32_t	UInt32Arg::getMin() const { return _min; }
uint32_t	UInt32Arg::getMax() const { return _max; };
std::pair<uint32_t, bool>	UInt32Arg::getDefaultV() const { return _defaultV; }
std::pair<uint32_t, bool>	UInt32Arg::getVal() const { return _value; }
void		UInt32Arg::setVal(std::string strVal) {
	(void)strVal;
	_value = {42, true};
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
		logWarn("you have set a default value lesser than the minimal value");
	}
	else if (defaultV > _max) {
		logWarn("you have set a default value bigger than the maximal value");
	}
	this->_defaultV = {defaultV, true};
	_value = {defaultV, true};  // update _value accordingly
	return *this;
};
AInfoArg	&UInt64Arg::setMinUI64(uint64_t min) {
	if (_defaultV.second && _defaultV.first < min) {
		logWarn("you have set a minimal value bigger than the default value");
	}
	this->_min = min;
	return *this;
};
AInfoArg	&UInt64Arg::setMaxUI64(uint64_t max) {
	if (_defaultV.second && _defaultV.first > max) {
		logWarn("you have set a maximal value lesser than the default value");
	}
	this->_max = max;
	return *this;
};

uint64_t	UInt64Arg::getMin() const { return _min; }
uint64_t	UInt64Arg::getMax() const { return _max; };
std::pair<uint64_t, bool>	UInt64Arg::getDefaultV() const { return _defaultV; }
std::pair<uint64_t, bool>	UInt64Arg::getVal() const { return _value; }
void		UInt64Arg::setVal(std::string strVal) {
	(void)strVal;
	_value = {42, true};
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
	this->_defaultV = {defaultV, true};
	_value = {defaultV, true};  // update _value accordingly
	return *this;
};
AInfoArg	&FloatArg::setMinF(float min) {
	this->_min = min;
	return *this;
};
AInfoArg	&FloatArg::setMaxF(float max) {
	this->_max = max;
	return *this;
};

float	FloatArg::getMin() const { return _min; }
float	FloatArg::getMax() const { return _max; };
std::pair<float, bool>	FloatArg::getDefaultV() const { return _defaultV; }
std::pair<float, bool>	FloatArg::getVal() const { return _value; }
void	FloatArg::setVal(std::string strVal) {
	(void)strVal;
	_value = {42.0, true};
}
// --
