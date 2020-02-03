#include "ArgInfo.hpp"
#include <limits>
#include <iomanip>

#include "Logging.hpp"

// -- ArgInfo ------------------------------------------------------------------
ArgInfo::ArgInfo()
: type(ArgType::STRING),
  required(false) {
}

ArgInfo::ArgInfo(ArgType::Enum type)
: type(type),
  required(false) {
}

ArgInfo::~ArgInfo() {
}

ArgInfo::ArgInfo(ArgInfo const &src) {
	*this = src;
}

ArgInfo &ArgInfo::operator=(ArgInfo const &rhs) {
	if (this != &rhs) {
		type = rhs.type;
		shortName = rhs.shortName;
		longName = rhs.longName;
		help = rhs.help;
		required = rhs.required;
	}
	return *this;
}

void ArgInfo::print(std::ostream &out) const {
	out << std::boolalpha << "{ type: " << ArgType::enumNames[type] << \
	", shortName: \"" << shortName << "\", longName: \"" << longName << \
	"\", help: \"" << help << "\", required: " << required;
}

ArgInfo	&ArgInfo::setShortName(std::string shortName) {
	this->shortName = shortName;
	return *this;
}
ArgInfo	&ArgInfo::setLongName(std::string longName) {
	this->longName = longName;
	return *this;
}
ArgInfo	&ArgInfo::setHelp(std::string help) {
	this->help = help;
	return *this;
}
ArgInfo	&ArgInfo::isRequired(bool required) {
	this->required = required;
	return *this;
}

ArgInfo	&ArgInfo::setMinI(int min) {
	(void)min;
	logErr("[" << ArgType::enumNames[type] << "] unknow setMinI function");
	return *this;
}
ArgInfo	&ArgInfo::setMinF(float min) {
	(void)min;
	logErr("[" << ArgType::enumNames[type] << "] unknow setMinF function");
	return *this;
}
ArgInfo	&ArgInfo::setMaxI(int max) {
	(void)max;
	logErr("[" << ArgType::enumNames[type] << "] unknow setMaxI function");
	return *this;
}
ArgInfo	&ArgInfo::setMaxF(float max) {
	(void)max;
	logErr("[" << ArgType::enumNames[type] << "] unknow setMaxF function");
	return *this;
}
ArgInfo	&ArgInfo::setStoreTrue(bool storeTrue) {
	(void)storeTrue;
	logErr("[" << ArgType::enumNames[type] << "] unknow setStoreTrue function");
	return *this;
}

ArgInfo	&ArgInfo::setDefaultS(std::string defaultV) {
	(void)defaultV;
	logErr("[" << ArgType::enumNames[type] << "] unknow setDefaultS function");
	return *this;
}
ArgInfo	&ArgInfo::setDefaultB(bool defaultV) {
	(void)defaultV;
	logErr("[" << ArgType::enumNames[type] << "] unknow setDefaultB function");
	return *this;
}
ArgInfo	&ArgInfo::setDefaultI(int defaultV) {
	(void)defaultV;
	logErr("[" << ArgType::enumNames[type] << "] unknow setDefaultI function");
	return *this;
}
ArgInfo	&ArgInfo::setDefaultF(float defaultV) {
	(void)defaultV;
	logErr("[" << ArgType::enumNames[type] << "] unknow setDefaultF function");
	return *this;
}

std::ostream & operator << (std::ostream &out, const ArgInfo &aInfo) {
	aInfo.print(out);  // delegate the work to the polymorphic member function
	return out;
}

// -- StringArg ----------------------------------------------------------------
StringArg::StringArg()
: ArgInfo(ArgType::STRING),
  min(0),
  max(std::numeric_limits<int>::max()) {
}

StringArg::~StringArg() {
}

StringArg::StringArg(StringArg const &src): ArgInfo(src) {
	*this = src;
}

StringArg &StringArg::operator=(StringArg const &rhs) {
	ArgInfo::operator=(rhs);
	if (this != &rhs) {
		min = rhs.min;
		max = rhs.max;
		defaultV = rhs.defaultV;
	}
	return *this;
}

void StringArg::print(std::ostream &out) const {
	ArgInfo::print(out);
	out << ", min: " << min << ", max: " << max << ", defaultV: \"" << defaultV << "\" }";
}

ArgInfo	&StringArg::setDefaultS(std::string defaultV) {
	this->defaultV = defaultV;
	return *this;
}
ArgInfo	&StringArg::setMinI(int min) {
	this->min = min;
	return *this;
}
ArgInfo	&StringArg::setMaxI(int max) {
	this->max = max;
	return *this;
}

// -- BoolArg ------------------------------------------------------------------
BoolArg::BoolArg()
: ArgInfo(ArgType::BOOL),
  defaultV(false),
  storeTrue(false) {
}

BoolArg::~BoolArg() {
}

BoolArg::BoolArg(BoolArg const &src): ArgInfo(src) {
	*this = src;
}

BoolArg &BoolArg::operator=(BoolArg const &rhs) {
	ArgInfo::operator=(rhs);
	if (this != &rhs) {
		defaultV = rhs.defaultV;
		storeTrue = rhs.storeTrue;
	}
	return *this;
}

void BoolArg::print(std::ostream &out) const {
	ArgInfo::print(out);
	out << ", defaultV: " << defaultV << ", storeTrue: " << storeTrue << " }";
}

ArgInfo	&BoolArg::setDefaultB(bool defaultV) {
	this->defaultV = defaultV;
	return *this;
}
ArgInfo	&BoolArg::setStoreTrue(bool storeTrue) {
	this->storeTrue = storeTrue;
	return *this;
}

// -- IntArg -------------------------------------------------------------------
IntArg::IntArg()
: ArgInfo(ArgType::INT),
  min(std::numeric_limits<int>::lowest()),
  max(std::numeric_limits<int>::max()),
  defaultV(0) {
}

IntArg::~IntArg() {
}

IntArg::IntArg(IntArg const &src): ArgInfo(src) {
	*this = src;
}

IntArg &IntArg::operator=(IntArg const &rhs) {
	ArgInfo::operator=(rhs);
	if (this != &rhs) {
		min = rhs.min;
		max = rhs.max;
		defaultV = rhs.defaultV;
	}
	return *this;
}

void IntArg::print(std::ostream &out) const {
	ArgInfo::print(out);
	out << ", min: " << min << ", max: " << max << ", defaultV: " << defaultV << " }";
}

ArgInfo	&IntArg::setDefaultI(int defaultV) {
	this->defaultV = defaultV;
	return *this;
};
ArgInfo	&IntArg::setMinI(int min) {
	this->min = min;
	return *this;
};
ArgInfo	&IntArg::setMaxI(int max) {
	this->max = max;
	return *this;
};

// -- FloatArg -----------------------------------------------------------------
FloatArg::FloatArg()
: ArgInfo(ArgType::FLOAT),
  min(std::numeric_limits<float>::lowest()),
  max(std::numeric_limits<float>::max()),
  defaultV(0.0f) {
}

FloatArg::~FloatArg() {
}

FloatArg::FloatArg(FloatArg const &src): ArgInfo(src) {
	*this = src;
}

FloatArg &FloatArg::operator=(FloatArg const &rhs) {
	ArgInfo::operator=(rhs);
	if (this != &rhs) {
		min = rhs.min;
		max = rhs.max;
		defaultV = rhs.defaultV;
	}
	return *this;
}

void FloatArg::print(std::ostream &out) const {
	ArgInfo::print(out);
	out << ", min: " << min << ", max: " << max << ", defaultV: " << defaultV << " }";
}

ArgInfo	&FloatArg::setDefaultF(float defaultV) {
	this->defaultV = defaultV;
	return *this;
};
ArgInfo	&FloatArg::setMinF(float min) {
	this->min = min;
	return *this;
};
ArgInfo	&FloatArg::setMaxF(float max) {
	this->max = max;
	return *this;
};
