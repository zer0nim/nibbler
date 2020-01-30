#include "ArgInfo.hpp"

// -- ArgInfo ------------------------------------------------------------------
ArgInfo::ArgInfo() {
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

// -- StringArg ----------------------------------------------------------------
StringArg::StringArg() {
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

// -- BoolArg ------------------------------------------------------------------
BoolArg::BoolArg() {
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

// -- IntArg -------------------------------------------------------------------
IntArg::IntArg() {
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

// -- FloatArg -----------------------------------------------------------------
FloatArg::FloatArg() {
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
