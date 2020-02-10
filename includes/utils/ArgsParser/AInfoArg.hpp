#ifndef AINFOARG_HPP_
#define AINFOARG_HPP_

#define A_NO_NAME 0

#include <iostream>
#include <string>
#include <array>
#include <type_traits>

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


// -- AInfoArg -----------------------------------------------------------------
class AInfoArg {
	public:
		virtual				~AInfoArg();

		// -- common settings func ---------------------------------------------
		AInfoArg			&setOptional(std::string const &longName, char shortName = A_NO_NAME);
		AInfoArg			&setOptional(char shortName, std::string const &longName = "");
		AInfoArg			&setHelp(std::string help);

		// -- args settings func -----------------------------------------------
		virtual AInfoArg	&setDefaultS(std::string defaultV);
		virtual AInfoArg	&setDefaultB(bool defaultV);
		// floating point
		virtual AInfoArg	&setDefaultF(double defaultV);
		virtual AInfoArg	&setMinF(double min);
		virtual AInfoArg	&setMaxF(double max);
		// signed integral
		virtual AInfoArg	&setDefaultI(int64_t defaultV);
		virtual AInfoArg	&setMinI(int64_t min);
		virtual AInfoArg	&setMaxI(int64_t max);
		// unsigned integral
		virtual AInfoArg	&setDefaultU(uint64_t defaultV);
		virtual AInfoArg	&setMinU(uint64_t min);
		virtual AInfoArg	&setMaxU(uint64_t max);

		virtual AInfoArg	&setStoreTrue(bool storeTrue = true);

		// transform the string val to the type val
		virtual	void		setVal(std::string input) = 0;
		virtual void		print(std::ostream &out) const;

		// -- getters ----------------------------------------------------------
		bool				needArgument() const;
		ArgType::Enum		getType() const;
		std::string const	&getName() const;
		char				getShortName() const;
		std::string const	&getLongName() const;
		std::string const	&getHelp() const;
		bool				getRequired() const;

		// -- exceptions -------------------------------------------------------
		class AInfoArgError : public std::runtime_error {
			public:
				AInfoArgError();
				explicit AInfoArgError(const char* what_arg);
		};

	protected:
		explicit	AInfoArg(ArgsParser *argsParser, std::string name, ArgType::Enum type);
		AInfoArg(AInfoArg const &src);
		AInfoArg	&operator=(AInfoArg const &rhs);

		ArgType::Enum	_type;
		std::string		_name;
		char			_shortName;
		std::string		_longName;
		std::string		_help;
		bool			_required;

	private:
		AInfoArg();
		void	unknownFunction(std::string const &funcName);

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
		virtual AInfoArg	&setMinU(uint64_t min);
		virtual AInfoArg	&setMaxU(uint64_t max);

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

#endif  // AINFOARG_HPP_
