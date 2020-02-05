#ifndef ARGINFO_HPP_
#define ARGINFO_HPP_

#define A_NO_NAME 0

#include <iostream>
#include <string>
#include <array>

#include "Logging.hpp"

class ArgsParser;  // to avoid circular dependency

// COLOR_GREEN
#define COLOR_TYPE "\x1B[32m"
// COLOR_CYAN
#define COLOR_L_VAL "\x1B[36m"
// COLOR_MAGENTA
#define COLOR_R_VAL "\x1B[35m"

namespace ArgType {
	enum Enum {
		STRING,
		BOOL,
		INT32,
		INT64,
		UINT32,
		UINT64,
		FLOAT
	};

	const std::array<std::string, 7>	enumNames = {
		"string",
		"bool",
		"int32",
		"int64",
		"uint32",
		"uint64",
		"float"
	};
}  // namespace ArgType


// -- ArgInfo ------------------------------------------------------------------
class ArgInfo {
	public:
		virtual ~ArgInfo();
		virtual void print(std::ostream &out) const;
		bool	needArgument() const;

		ArgInfo	&setOptional(std::string const &longName, char shortName = A_NO_NAME);
		ArgInfo	&setOptional(char shortName, std::string const &longName = "");
		ArgInfo	&setHelp(std::string help);

		virtual ArgInfo	&setDefaultS(std::string defaultV);
		virtual ArgInfo	&setDefaultB(bool defaultV);
		virtual ArgInfo	&setDefaultI32(int32_t defaultV);
		virtual ArgInfo	&setDefaultI64(int64_t defaultV);
		virtual ArgInfo	&setDefaultUI32(uint32_t defaultV);
		virtual ArgInfo	&setDefaultUI64(uint64_t defaultV);
		virtual ArgInfo	&setDefaultF(float defaultV);

		virtual ArgInfo	&setMinI32(int32_t min);
		virtual ArgInfo	&setMaxI32(int32_t max);
		virtual ArgInfo	&setMinI64(int64_t min);
		virtual ArgInfo	&setMaxI64(int64_t max);
		virtual ArgInfo	&setMinUI32(uint32_t min);
		virtual ArgInfo	&setMaxUI32(uint32_t max);
		virtual ArgInfo	&setMinUI64(uint64_t min);
		virtual ArgInfo	&setMaxUI64(uint64_t max);
		virtual ArgInfo	&setMinF(float min);
		virtual ArgInfo	&setMaxF(float max);
		virtual ArgInfo	&setMinLength(uint32_t min);
		virtual ArgInfo	&setMaxLength(uint32_t max);
		virtual ArgInfo	&setStoreTrue(bool storeTrue = true);

		ArgType::Enum		getType() const;
		std::string const	&getName() const;
		char				getShortName() const;
		std::string const	&getLongName() const;
		std::string const	&getHelp() const;
		bool				getRequired() const;

	protected:
		explicit ArgInfo(ArgsParser *argsParser, std::string name, ArgType::Enum type);
		ArgInfo(ArgInfo const &src);
		ArgInfo &operator=(ArgInfo const &rhs);

		ArgType::Enum	_type;
		std::string		_name;
		char			_shortName;
		std::string		_longName;
		std::string		_help;
		bool			_required;

	private:
		ArgInfo();

		ArgsParser	*_argsParser;
};

std::ostream & operator << (std::ostream &out, const ArgInfo &aInfo);

// used to avoid name duplicates
struct ArgInfoPtrComp {
	bool operator()(ArgInfo const *lhs, ArgInfo const *rhs) const;
};

// -- StringArg ----------------------------------------------------------------
class StringArg : public ArgInfo {
	public:
		StringArg(ArgsParser *argsParser, std::string name);
		virtual ~StringArg();
		StringArg(StringArg const &src);
		StringArg &operator=(StringArg const &rhs);

		virtual void print(std::ostream &out) const;

		virtual ArgInfo	&setDefaultS(std::string defaultV);
		virtual ArgInfo	&setMinLength(uint32_t min);
		virtual ArgInfo	&setMaxLength(uint32_t max);

		uint32_t		getMin() const;  // min string lenght
		uint32_t		getMax() const;  // max string lenght
		std::string		getDefaultV() const;

	private:
		StringArg();

		uint32_t		_min;  // min string lenght
		uint32_t		_max;  // max string lenght
		std::string		_defaultV;
};

// -- BoolArg ------------------------------------------------------------------
class BoolArg : public ArgInfo {
	public:
		BoolArg(ArgsParser *argsParser, std::string name);
		virtual ~BoolArg();
		BoolArg(BoolArg const &src);
		BoolArg &operator=(BoolArg const &rhs);

		virtual void print(std::ostream &out) const;

		virtual ArgInfo	&setDefaultB(bool defaultV);
		virtual ArgInfo	&setStoreTrue(bool storeTrue = true);

		bool	getDefaultV() const;
		bool	getStoreTrue() const;  // allow to skip val for bool

	private:
		BoolArg();

		bool	_defaultV;
		bool	_storeTrue;  // allow to skip val for bool
};

// -- Int32Arg -------------------------------------------------------------------
class Int32Arg : public ArgInfo {
	public:
		Int32Arg(ArgsParser *argsParser, std::string name);
		virtual ~Int32Arg();
		Int32Arg(Int32Arg const &src);
		Int32Arg &operator=(Int32Arg const &rhs);

		virtual void print(std::ostream &out) const;

		virtual ArgInfo	&setDefaultI32(int32_t defaultV);
		virtual ArgInfo	&setMinI32(int32_t min);
		virtual ArgInfo	&setMaxI32(int32_t max);

		int32_t	getMin() const;
		int32_t	getMax() const;
		int32_t	getDefaultV() const;

	private:
		Int32Arg();

		int32_t	_min;
		int32_t	_max;
		int32_t	_defaultV;
};

// -- Int64Arg -------------------------------------------------------------------
class Int64Arg : public ArgInfo {
	public:
		Int64Arg(ArgsParser *argsParser, std::string name);
		virtual ~Int64Arg();
		Int64Arg(Int64Arg const &src);
		Int64Arg &operator=(Int64Arg const &rhs);

		virtual void print(std::ostream &out) const;

		virtual ArgInfo	&setDefaultI64(int64_t defaultV);
		virtual ArgInfo	&setMinI64(int64_t min);
		virtual ArgInfo	&setMaxI64(int64_t max);

		int64_t	getMin() const;
		int64_t	getMax() const;
		int64_t	getDefaultV() const;

	private:
		Int64Arg();

		int64_t	_min;
		int64_t	_max;
		int64_t	_defaultV;
};

// -- UInt32Arg -------------------------------------------------------------------
class UInt32Arg : public ArgInfo {
	public:
		UInt32Arg(ArgsParser *argsParser, std::string name);
		virtual ~UInt32Arg();
		UInt32Arg(UInt32Arg const &src);
		UInt32Arg &operator=(UInt32Arg const &rhs);

		virtual void print(std::ostream &out) const;

		virtual ArgInfo	&setDefaultUI32(uint32_t defaultV);
		virtual ArgInfo	&setMinUI32(uint32_t min);
		virtual ArgInfo	&setMaxUI32(uint32_t max);

		uint32_t	getMin() const;
		uint32_t	getMax() const;
		uint32_t	getDefaultV() const;

	private:
		UInt32Arg();

		uint32_t	_min;
		uint32_t	_max;
		uint32_t	_defaultV;
};

// -- UInt64Arg -------------------------------------------------------------------
class UInt64Arg : public ArgInfo {
	public:
		UInt64Arg(ArgsParser *argsParser, std::string name);
		virtual ~UInt64Arg();
		UInt64Arg(UInt64Arg const &src);
		UInt64Arg &operator=(UInt64Arg const &rhs);

		virtual void print(std::ostream &out) const;

		virtual ArgInfo	&setDefaultUI64(uint64_t defaultV);
		virtual ArgInfo	&setMinUI64(uint64_t min);
		virtual ArgInfo	&setMaxUI64(uint64_t max);

		uint64_t	getMin() const;
		uint64_t	getMax() const;
		uint64_t	getDefaultV() const;

	private:
		UInt64Arg();

		uint64_t	_min;
		uint64_t	_max;
		uint64_t	_defaultV;
};

// -- FloatArg -----------------------------------------------------------------
class FloatArg : public ArgInfo {
	public:
		FloatArg(ArgsParser *argsParser, std::string name);
		virtual ~FloatArg();
		FloatArg(FloatArg const &src);
		FloatArg &operator=(FloatArg const &rhs);

		virtual void print(std::ostream &out) const;

		virtual ArgInfo	&setDefaultF(float defaultV);
		virtual ArgInfo	&setMinF(float min);
		virtual ArgInfo	&setMaxF(float max);

		float	getMin() const;
		float	getMax() const;
		float	getDefaultV() const;

	private:
		FloatArg();

		float	_min;
		float	_max;
		float	_defaultV;
};

#endif  // ARGINFO_HPP_
