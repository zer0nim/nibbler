#ifndef AINFOARG_HPP_
#define AINFOARG_HPP_

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


// -- AInfoArg ------------------------------------------------------------------
class AInfoArg {
	public:
		virtual ~AInfoArg();
		virtual void print(std::ostream &out) const;
		bool	needArgument() const;

		AInfoArg	&setOptional(std::string const &longName, char shortName = A_NO_NAME);
		AInfoArg	&setOptional(char shortName, std::string const &longName = "");
		AInfoArg	&setHelp(std::string help);

		virtual AInfoArg	&setDefaultS(std::string defaultV);
		virtual AInfoArg	&setDefaultB(bool defaultV);
		virtual AInfoArg	&setDefaultI32(int32_t defaultV);
		virtual AInfoArg	&setDefaultI64(int64_t defaultV);
		virtual AInfoArg	&setDefaultUI32(uint32_t defaultV);
		virtual AInfoArg	&setDefaultUI64(uint64_t defaultV);
		virtual AInfoArg	&setDefaultF(float defaultV);

		virtual AInfoArg	&setMinI32(int32_t min);
		virtual AInfoArg	&setMaxI32(int32_t max);
		virtual AInfoArg	&setMinI64(int64_t min);
		virtual AInfoArg	&setMaxI64(int64_t max);
		virtual AInfoArg	&setMinUI32(uint32_t min);
		virtual AInfoArg	&setMaxUI32(uint32_t max);
		virtual AInfoArg	&setMinUI64(uint64_t min);
		virtual AInfoArg	&setMaxUI64(uint64_t max);
		virtual AInfoArg	&setMinF(float min);
		virtual AInfoArg	&setMaxF(float max);
		virtual AInfoArg	&setMinLength(uint32_t min);
		virtual AInfoArg	&setMaxLength(uint32_t max);
		virtual AInfoArg	&setStoreTrue(bool storeTrue = true);

		// transform the string val to the type val
		virtual	void	setVal(std::string input) = 0;

		ArgType::Enum		getType() const;
		std::string const	&getName() const;
		char				getShortName() const;
		std::string const	&getLongName() const;
		std::string const	&getHelp() const;
		bool				getRequired() const;

	protected:
		explicit AInfoArg(ArgsParser *argsParser, std::string name, ArgType::Enum type);
		AInfoArg(AInfoArg const &src);
		AInfoArg &operator=(AInfoArg const &rhs);

		ArgType::Enum	_type;
		std::string		_name;
		char			_shortName;
		std::string		_longName;
		std::string		_help;
		bool			_required;

	private:
		AInfoArg();

		ArgsParser	*_argsParser;
};

std::ostream & operator << (std::ostream &out, const AInfoArg &aInfo);

// -- StringArg ----------------------------------------------------------------
class StringArg : public AInfoArg {
	public:
		StringArg(ArgsParser *argsParser, std::string name);
		virtual ~StringArg();
		StringArg(StringArg const &src);
		StringArg &operator=(StringArg const &rhs);

		virtual void print(std::ostream &out) const;

		virtual AInfoArg	&setDefaultS(std::string defaultV);
		virtual AInfoArg	&setMinLength(uint32_t min);
		virtual AInfoArg	&setMaxLength(uint32_t max);

		uint32_t		getMin() const;  // min string lenght
		uint32_t		getMax() const;  // max string lenght
		std::pair<std::string, bool>	getDefaultV() const;
		std::pair<std::string, bool>	getVal() const;

		virtual	void	setVal(std::string input);

	private:
		StringArg();

		uint32_t		_min;  // min string lenght
		uint32_t		_max;  // max string lenght
		std::pair<std::string, bool>	_defaultV;
		std::pair<std::string, bool>	_value;
};

// -- BoolArg ------------------------------------------------------------------
class BoolArg : public AInfoArg {
	public:
		BoolArg(ArgsParser *argsParser, std::string name);
		virtual ~BoolArg();
		BoolArg(BoolArg const &src);
		BoolArg &operator=(BoolArg const &rhs);

		virtual void print(std::ostream &out) const;

		virtual AInfoArg	&setDefaultB(bool defaultV);
		virtual AInfoArg	&setStoreTrue(bool storeTrue = true);

		bool	getDefaultV() const;
		bool	getStoreTrue() const;  // allow to skip val for bool
		std::pair<bool, bool>	getVal() const;

		virtual	void	setVal(std::string input);

	private:
		BoolArg();

		bool	_defaultV;
		bool	_storeTrue;  // allow to skip val for bool
		std::pair<bool, bool>	_value;
};

// -- Int32Arg -------------------------------------------------------------------
class Int32Arg : public AInfoArg {
	public:
		Int32Arg(ArgsParser *argsParser, std::string name);
		virtual ~Int32Arg();
		Int32Arg(Int32Arg const &src);
		Int32Arg &operator=(Int32Arg const &rhs);

		virtual void print(std::ostream &out) const;

		virtual AInfoArg	&setDefaultI32(int32_t defaultV);
		virtual AInfoArg	&setMinI32(int32_t min);
		virtual AInfoArg	&setMaxI32(int32_t max);

		int32_t	getMin() const;
		int32_t	getMax() const;
		std::pair<int32_t, bool>	getDefaultV() const;
		std::pair<int32_t, bool>	getVal() const;

		virtual	void	setVal(std::string input);

	private:
		Int32Arg();

		int32_t	_min;
		int32_t	_max;
		std::pair<int32_t, bool>	_defaultV;
		std::pair<int32_t, bool>	_value;
};

// -- Int64Arg -------------------------------------------------------------------
class Int64Arg : public AInfoArg {
	public:
		Int64Arg(ArgsParser *argsParser, std::string name);
		virtual ~Int64Arg();
		Int64Arg(Int64Arg const &src);
		Int64Arg &operator=(Int64Arg const &rhs);

		virtual void print(std::ostream &out) const;

		virtual AInfoArg	&setDefaultI64(int64_t defaultV);
		virtual AInfoArg	&setMinI64(int64_t min);
		virtual AInfoArg	&setMaxI64(int64_t max);

		int64_t	getMin() const;
		int64_t	getMax() const;
		std::pair<int64_t, bool>	getDefaultV() const;
		std::pair<int64_t, bool>	getVal() const;

		virtual	void	setVal(std::string input);

	private:
		Int64Arg();

		int64_t	_min;
		int64_t	_max;
		std::pair<int64_t, bool>	_defaultV;
		std::pair<int64_t, bool>	_value;
};

// -- UInt32Arg -------------------------------------------------------------------
class UInt32Arg : public AInfoArg {
	public:
		UInt32Arg(ArgsParser *argsParser, std::string name);
		virtual ~UInt32Arg();
		UInt32Arg(UInt32Arg const &src);
		UInt32Arg &operator=(UInt32Arg const &rhs);

		virtual void print(std::ostream &out) const;

		virtual AInfoArg	&setDefaultUI32(uint32_t defaultV);
		virtual AInfoArg	&setMinUI32(uint32_t min);
		virtual AInfoArg	&setMaxUI32(uint32_t max);

		uint32_t	getMin() const;
		uint32_t	getMax() const;
		std::pair<uint32_t, bool>	getDefaultV() const;
		std::pair<uint32_t, bool>	getVal() const;

		virtual	void	setVal(std::string input);

	private:
		UInt32Arg();

		uint32_t	_min;
		uint32_t	_max;
		std::pair<uint32_t, bool>	_defaultV;
		std::pair<uint32_t, bool>	_value;
};

// -- UInt64Arg -------------------------------------------------------------------
class UInt64Arg : public AInfoArg {
	public:
		UInt64Arg(ArgsParser *argsParser, std::string name);
		virtual ~UInt64Arg();
		UInt64Arg(UInt64Arg const &src);
		UInt64Arg &operator=(UInt64Arg const &rhs);

		virtual void print(std::ostream &out) const;

		virtual AInfoArg	&setDefaultUI64(uint64_t defaultV);
		virtual AInfoArg	&setMinUI64(uint64_t min);
		virtual AInfoArg	&setMaxUI64(uint64_t max);

		uint64_t	getMin() const;
		uint64_t	getMax() const;
		std::pair<uint64_t, bool>	getDefaultV() const;
		std::pair<uint64_t, bool>	getVal() const;

		virtual	void	setVal(std::string input);

	private:
		UInt64Arg();

		uint64_t	_min;
		uint64_t	_max;
		std::pair<uint64_t, bool>	_defaultV;
		std::pair<uint64_t, bool>	_value;
};

// -- FloatArg -----------------------------------------------------------------
class FloatArg : public AInfoArg {
	public:
		FloatArg(ArgsParser *argsParser, std::string name);
		virtual ~FloatArg();
		FloatArg(FloatArg const &src);
		FloatArg &operator=(FloatArg const &rhs);

		virtual void print(std::ostream &out) const;

		virtual AInfoArg	&setDefaultF(float defaultV);
		virtual AInfoArg	&setMinF(float min);
		virtual AInfoArg	&setMaxF(float max);

		float	getMin() const;
		float	getMax() const;
		std::pair<float, bool>	getDefaultV() const;
		std::pair<float, bool>	getVal() const;

		virtual	void	setVal(std::string input);

	private:
		FloatArg();

		float	_min;
		float	_max;
		std::pair<float, bool>	_defaultV;
		std::pair<float, bool>	_value;
};

#endif  // AINFOARG_HPP_
