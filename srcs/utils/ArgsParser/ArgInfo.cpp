#include "ArgInfo.hpp"
#include <limits>

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
	out << "{ type: " << ArgType::enumNames[type] << \
	", shortName: \"" << shortName << "\", longName: \"" << longName << \
	"\", help: \"" << help << "\", required: " << required;
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
