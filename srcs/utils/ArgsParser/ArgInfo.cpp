#include "ArgInfo.hpp"
#include <limits>
#include <iomanip>

#include "Logging.hpp"

// -- ArgInfo ------------------------------------------------------------------
ArgInfo::ArgInfo()
: type(ArgType::STRING),
  name("noName"),
  shortName(A_NO_NAME),
  required(true) {
	  logErr("this constructor should not be called")
}

ArgInfo::ArgInfo(std::string name, ArgType::Enum type)
: type(type),
  name(name),
  shortName(A_NO_NAME),
  required(true) {
}

ArgInfo::~ArgInfo() {
}

ArgInfo::ArgInfo(ArgInfo const &src) {
	*this = src;
}

ArgInfo &ArgInfo::operator=(ArgInfo const &rhs) {
	if (this != &rhs) {
		type = rhs.type;
		name = rhs.name;
		shortName = rhs.shortName;
		longName = rhs.longName;
		help = rhs.help;
		required = rhs.required;
	}
	return *this;
}

void ArgInfo::print(std::ostream &out) const {
	out << "<" << ArgType::enumNames[type];
}

// set optionnals arguments name
ArgInfo	&ArgInfo::setOptional(std::string longName, char shortName) {
	required = false;  // disable required for optionnals args
	this->shortName = shortName;
	this->longName = longName;
	return *this;
}

ArgInfo	&ArgInfo::setHelp(std::string help) {
	this->help = help;
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
ArgInfo	&ArgInfo::setDefaultI32(int32_t defaultV) {
	(void)defaultV;
	logErr("[" << ArgType::enumNames[type] << "] unknow setDefaultI32 function");
	return *this;
}
ArgInfo	&ArgInfo::setDefaultI64(int64_t defaultV) {
	(void)defaultV;
	logErr("[" << ArgType::enumNames[type] << "] unknow setDefaultI64 function");
	return *this;
}
ArgInfo	&ArgInfo::setDefaultUI32(uint32_t defaultV) {
	(void)defaultV;
	logErr("[" << ArgType::enumNames[type] << "] unknow setDefaultUI32 function");
	return *this;
}
ArgInfo	&ArgInfo::setDefaultUI64(uint64_t defaultV) {
	(void)defaultV;
	logErr("[" << ArgType::enumNames[type] << "] unknow setDefaultUI64 function");
	return *this;
}
ArgInfo	&ArgInfo::setDefaultF(float defaultV) {
	(void)defaultV;
	logErr("[" << ArgType::enumNames[type] << "] unknow setDefaultF function");
	return *this;
}
ArgInfo	&ArgInfo::setMinI32(int32_t min) {
	(void)min;
	logErr("[" << ArgType::enumNames[type] << "] unknow setMinI32 function");
	return *this;
}
ArgInfo	&ArgInfo::setMaxI32(int32_t max) {
	(void)max;
	logErr("[" << ArgType::enumNames[type] << "] unknow setMaxI32 function");
	return *this;
}
ArgInfo	&ArgInfo::setMinI64(int64_t min) {
	(void)min;
	logErr("[" << ArgType::enumNames[type] << "] unknow setMinI64 function");
	return *this;
}
ArgInfo	&ArgInfo::setMaxI64(int64_t max) {
	(void)max;
	logErr("[" << ArgType::enumNames[type] << "] unknow setMaxI64 function");
	return *this;
}
ArgInfo	&ArgInfo::setMinUI32(uint32_t min) {
	(void)min;
	logErr("[" << ArgType::enumNames[type] << "] unknow setMinUI32 function");
	return *this;
}
ArgInfo	&ArgInfo::setMaxUI32(uint32_t max) {
	(void)max;
	logErr("[" << ArgType::enumNames[type] << "] unknow setMaxUI32 function");
	return *this;
}
ArgInfo	&ArgInfo::setMinUI64(uint64_t min) {
	(void)min;
	logErr("[" << ArgType::enumNames[type] << "] unknow setMinUI64 function");
	return *this;
}
ArgInfo	&ArgInfo::setMaxUI64(uint64_t max) {
	(void)max;
	logErr("[" << ArgType::enumNames[type] << "] unknow setMaxUI64 function");
	return *this;
}
ArgInfo	&ArgInfo::setMinF(float min) {
	(void)min;
	logErr("[" << ArgType::enumNames[type] << "] unknow setMinF function");
	return *this;
}
ArgInfo	&ArgInfo::setMaxF(float max) {
	(void)max;
	logErr("[" << ArgType::enumNames[type] << "] unknow setMaxF function");
	return *this;
}
ArgInfo	&ArgInfo::setMinLength(uint32_t min) {
	(void)min;
	logErr("[" << ArgType::enumNames[type] << "] unknow setMinLength function");
	return *this;
}
ArgInfo	&ArgInfo::setMaxLength(uint32_t max) {
	(void)max;
	logErr("[" << ArgType::enumNames[type] << "] unknow setMaxLength function");
	return *this;
}
ArgInfo	&ArgInfo::setStoreTrue(bool storeTrue) {
	(void)storeTrue;
	logErr("[" << ArgType::enumNames[type] << "] unknow setStoreTrue function");
	return *this;
}

std::ostream & operator << (std::ostream &out, ArgInfo const &aInfo) {
	aInfo.print(out);  // delegate the work to the polymorphic member function
	return out;
}

// -- StringArg ----------------------------------------------------------------
StringArg::StringArg(std::string name)
: ArgInfo(name, ArgType::STRING),
  min(0),
  max(std::numeric_limits<uint32_t>::max()) {
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

	// print defaut string value
	if (defaultV != "") {
		out << " default=\"" << defaultV << "\"";
	}

	// print string min/max
	if (min != 0 || max != std::numeric_limits<uint32_t>::max()) {
		out << " length=[" << (min != 0 ? std::to_string(min) : "") << ":" << \
		(max != std::numeric_limits<uint32_t>::max() ? std::to_string(max) : "") \
		<< "]";
	}

	out << ">";
}

ArgInfo	&StringArg::setDefaultS(std::string defaultV) {
	this->defaultV = defaultV;
	return *this;
}
ArgInfo	&StringArg::setMinLength(uint32_t min) {
	this->min = min;
	return *this;
}
ArgInfo	&StringArg::setMaxLength(uint32_t max) {
	this->max = max;
	return *this;
}

// -- BoolArg ------------------------------------------------------------------
BoolArg::BoolArg(std::string name)
: ArgInfo(name, ArgType::BOOL),
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

	// print defaut string value
	if (!storeTrue) {
		out << " default=" << std::boolalpha << defaultV;
	}
	else {
		out << " storeTrue";
	}

	out << ">";
}

ArgInfo	&BoolArg::setDefaultB(bool defaultV) {
	this->defaultV = defaultV;
	return *this;
}
ArgInfo	&BoolArg::setStoreTrue(bool storeTrue) {
	this->storeTrue = storeTrue;
	return *this;
}

// -- Int32Arg -------------------------------------------------------------------
Int32Arg::Int32Arg(std::string name)
: ArgInfo(name, ArgType::INT32),
  min(std::numeric_limits<int32_t>::lowest()),
  max(std::numeric_limits<int32_t>::max()),
  defaultV(0) {
}

Int32Arg::~Int32Arg() {
}

Int32Arg::Int32Arg(Int32Arg const &src): ArgInfo(src) {
	*this = src;
}

Int32Arg &Int32Arg::operator=(Int32Arg const &rhs) {
	ArgInfo::operator=(rhs);
	if (this != &rhs) {
		min = rhs.min;
		max = rhs.max;
		defaultV = rhs.defaultV;
	}
	return *this;
}

void Int32Arg::print(std::ostream &out) const {
	ArgInfo::print(out);

	// print defaut int32_t value
	out << " default=" << defaultV;

	// print string min/max
	if (min != std::numeric_limits<int32_t>::lowest() || max != std::numeric_limits<int32_t>::max()) {
		out << " range=[" << \
			(min != std::numeric_limits<int32_t>::lowest() ? std::to_string(min) : "") << \
			":" << (max != std::numeric_limits<int32_t>::max() ? std::to_string(max) : "") \
			<< "]";
	}

	out << ">";
}

ArgInfo	&Int32Arg::setDefaultI32(int32_t defaultV) {
	this->defaultV = defaultV;
	return *this;
};
ArgInfo	&Int32Arg::setMinI32(int32_t min) {
	this->min = min;
	return *this;
};
ArgInfo	&Int32Arg::setMaxI32(int32_t max) {
	this->max = max;
	return *this;
};

// -- Int64Arg -------------------------------------------------------------------
Int64Arg::Int64Arg(std::string name)
: ArgInfo(name, ArgType::INT64),
  min(std::numeric_limits<int64_t>::lowest()),
  max(std::numeric_limits<int64_t>::max()),
  defaultV(0) {
}

Int64Arg::~Int64Arg() {
}

Int64Arg::Int64Arg(Int64Arg const &src): ArgInfo(src) {
	*this = src;
}

Int64Arg &Int64Arg::operator=(Int64Arg const &rhs) {
	ArgInfo::operator=(rhs);
	if (this != &rhs) {
		min = rhs.min;
		max = rhs.max;
		defaultV = rhs.defaultV;
	}
	return *this;
}

void Int64Arg::print(std::ostream &out) const {
	ArgInfo::print(out);

	// print defaut int64_t value
	out << " default=" << defaultV;

	// print string min/max
	if (min != std::numeric_limits<int64_t>::lowest() || max != std::numeric_limits<int64_t>::max()) {
		out << " range=[" << \
			(min != std::numeric_limits<int64_t>::lowest() ? std::to_string(min) : "") << \
			":" << (max != std::numeric_limits<int64_t>::max() ? std::to_string(max) : "") \
			<< "]";
	}

	out << ">";
}

ArgInfo	&Int64Arg::setDefaultI64(int64_t defaultV) {
	this->defaultV = defaultV;
	return *this;
};
ArgInfo	&Int64Arg::setMinI64(int64_t min) {
	this->min = min;
	return *this;
};
ArgInfo	&Int64Arg::setMaxI64(int64_t max) {
	this->max = max;
	return *this;
};

// -- UInt32Arg -------------------------------------------------------------------
UInt32Arg::UInt32Arg(std::string name)
: ArgInfo(name, ArgType::UINT32),
  min(std::numeric_limits<uint32_t>::lowest()),
  max(std::numeric_limits<uint32_t>::max()),
  defaultV(0) {
}

UInt32Arg::~UInt32Arg() {
}

UInt32Arg::UInt32Arg(UInt32Arg const &src): ArgInfo(src) {
	*this = src;
}

UInt32Arg &UInt32Arg::operator=(UInt32Arg const &rhs) {
	ArgInfo::operator=(rhs);
	if (this != &rhs) {
		min = rhs.min;
		max = rhs.max;
		defaultV = rhs.defaultV;
	}
	return *this;
}

void UInt32Arg::print(std::ostream &out) const {
	ArgInfo::print(out);

	// print defaut uint32_t value
	out << " default=" << defaultV;

	// print string min/max
	if (min != std::numeric_limits<uint32_t>::lowest() || max != std::numeric_limits<uint32_t>::max()) {
		out << " range=[" << \
			(min != std::numeric_limits<uint32_t>::lowest() ? std::to_string(min) : "") << \
			":" << (max != std::numeric_limits<uint32_t>::max() ? std::to_string(max) : "") \
			<< "]";
	}

	out << ">";
}

ArgInfo	&UInt32Arg::setDefaultUI32(uint32_t defaultV) {
	this->defaultV = defaultV;
	return *this;
};
ArgInfo	&UInt32Arg::setMinUI32(uint32_t min) {
	this->min = min;
	return *this;
};
ArgInfo	&UInt32Arg::setMaxUI32(uint32_t max) {
	this->max = max;
	return *this;
};

// -- UInt64Arg -------------------------------------------------------------------
UInt64Arg::UInt64Arg(std::string name)
: ArgInfo(name, ArgType::UINT64),
  min(std::numeric_limits<uint64_t>::lowest()),
  max(std::numeric_limits<uint64_t>::max()),
  defaultV(0) {
}

UInt64Arg::~UInt64Arg() {
}

UInt64Arg::UInt64Arg(UInt64Arg const &src): ArgInfo(src) {
	*this = src;
}

UInt64Arg &UInt64Arg::operator=(UInt64Arg const &rhs) {
	ArgInfo::operator=(rhs);
	if (this != &rhs) {
		min = rhs.min;
		max = rhs.max;
		defaultV = rhs.defaultV;
	}
	return *this;
}

void UInt64Arg::print(std::ostream &out) const {
	ArgInfo::print(out);

	// print defaut uint64_t value
	out << " default=" << defaultV;

	// print string min/max
	if (min != std::numeric_limits<uint64_t>::lowest() || max != std::numeric_limits<uint64_t>::max()) {
		out << " range=[" << \
			(min != std::numeric_limits<uint64_t>::lowest() ? std::to_string(min) : "") << \
			":" << (max != std::numeric_limits<uint64_t>::max() ? std::to_string(max) : "") \
			<< "]";
	}

	out << ">";
}

ArgInfo	&UInt64Arg::setDefaultUI64(uint64_t defaultV) {
	this->defaultV = defaultV;
	return *this;
};
ArgInfo	&UInt64Arg::setMinUI64(uint64_t min) {
	this->min = min;
	return *this;
};
ArgInfo	&UInt64Arg::setMaxUI64(uint64_t max) {
	this->max = max;
	return *this;
};

// -- FloatArg -----------------------------------------------------------------
FloatArg::FloatArg(std::string name)
: ArgInfo(name, ArgType::FLOAT),
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

	// print defaut int value
	out << " default=" << defaultV;

	// print string min/max
	if (min != std::numeric_limits<float>::lowest() || max != std::numeric_limits<float>::max()) {
		out << " range=[";
		if (min != std::numeric_limits<float>::lowest()) {
			out << std::fixed << std::setprecision(3) << min;
		}
		out << ":";
		if (max != std::numeric_limits<float>::max()) {
			out << std::fixed << std::setprecision(3) << max;
		}
		out << "]";
	}

	out << ">";
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