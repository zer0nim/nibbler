#ifndef ARGINFO_HPP_
#define ARGINFO_HPP_

#include <iostream>
#include <string>
#include <array>

namespace ArgType {
	enum Enum {
		STRING,
		BOOL,
		INT,
		FLOAT
	};

	const std::array<std::string, 4>	enumNames = {
		"string",
		"bool",
		"int",
		"float"
	};
}

// -- ArgInfo ------------------------------------------------------------------
class ArgInfo {
	public:
		virtual ~ArgInfo();
		virtual void print(std::ostream &out) const;

		ArgType::Enum	type;
		std::string		shortName;
		std::string		longName;
		std::string		help;
		bool			required;

	protected:
		ArgInfo(ArgType::Enum type);
		ArgInfo(ArgInfo const &src);
		ArgInfo &operator=(ArgInfo const &rhs);
	private:
		ArgInfo();

};

std::ostream & operator << (std::ostream &out, const ArgInfo &aInfo);

// -- StringArg ----------------------------------------------------------------
class StringArg : public ArgInfo {
	public:
		StringArg();
		virtual ~StringArg();
		StringArg(StringArg const &src);
		StringArg &operator=(StringArg const &rhs);

		virtual void print(std::ostream &out) const;

		int				min;  // min string lenght
		int				max;  // max string lenght
		std::string		defaultV;
};

// -- BoolArg ------------------------------------------------------------------
class BoolArg : public ArgInfo {
	public:
		BoolArg();
		virtual ~BoolArg();
		BoolArg(BoolArg const &src);
		BoolArg &operator=(BoolArg const &rhs);

		virtual void print(std::ostream &out) const;

		bool	defaultV;
		bool	storeTrue;  // allow to skip val for bool
};

// -- IntArg -------------------------------------------------------------------
class IntArg : public ArgInfo {
	public:
		IntArg();
		virtual ~IntArg();
		IntArg(IntArg const &src);
		IntArg &operator=(IntArg const &rhs);

		virtual void print(std::ostream &out) const;

		int		min;
		int		max;
		int		defaultV;
};

// -- FloatArg -----------------------------------------------------------------
class FloatArg : public ArgInfo {
	public:
		FloatArg();
		virtual ~FloatArg();
		FloatArg(FloatArg const &src);
		FloatArg &operator=(FloatArg const &rhs);

		virtual void print(std::ostream &out) const;

		float	min;
		float	max;
		float	defaultV;
};

#endif  // ARGINFO_HPP_
