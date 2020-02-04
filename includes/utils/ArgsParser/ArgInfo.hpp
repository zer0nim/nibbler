#ifndef ARGINFO_HPP_
#define ARGINFO_HPP_

#define A_NO_NAME 0

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
}  // namespace ArgType


// -- ArgInfo ------------------------------------------------------------------
class ArgInfo {
	public:
		virtual ~ArgInfo();
		virtual void print(std::ostream &out) const;

		ArgInfo	&setOptional(std::string longName, char shortName = A_NO_NAME);
		ArgInfo	&setHelp(std::string help);

		virtual ArgInfo	&setDefaultS(std::string defaultV);
		virtual ArgInfo	&setDefaultB(bool defaultV);
		virtual ArgInfo	&setDefaultI(int defaultV);
		virtual ArgInfo	&setDefaultF(float defaultV);

		virtual ArgInfo	&setMinI(int min);
		virtual ArgInfo	&setMinF(float min);
		virtual ArgInfo	&setMaxI(int max);
		virtual ArgInfo	&setMaxF(float max);
		virtual ArgInfo	&setStoreTrue(bool storeTrue = true);

		ArgType::Enum	type;
		std::string		name;
		char			shortName;
		std::string		longName;
		std::string		help;
		bool			required;

	protected:
		explicit ArgInfo(std::string name, ArgType::Enum type);
		ArgInfo(ArgInfo const &src);
		ArgInfo &operator=(ArgInfo const &rhs);

	private:
		ArgInfo();
};

// used to sort ArgInfo*
bool	compareArgInfoPtr(ArgInfo *lhs, ArgInfo *rhs);
std::ostream & operator << (std::ostream &out, const ArgInfo &aInfo);

// -- StringArg ----------------------------------------------------------------
class StringArg : public ArgInfo {
	public:
		explicit StringArg(std::string name);
		virtual ~StringArg();
		StringArg(StringArg const &src);
		StringArg &operator=(StringArg const &rhs);

		virtual void print(std::ostream &out) const;

		virtual ArgInfo	&setDefaultS(std::string defaultV);
		virtual ArgInfo	&setMinI(int min);
		virtual ArgInfo	&setMaxI(int max);

		int				min;  // min string lenght
		int				max;  // max string lenght
		std::string		defaultV;

	private:
		StringArg();
};

// -- BoolArg ------------------------------------------------------------------
class BoolArg : public ArgInfo {
	public:
		explicit BoolArg(std::string name);
		virtual ~BoolArg();
		BoolArg(BoolArg const &src);
		BoolArg &operator=(BoolArg const &rhs);

		virtual void print(std::ostream &out) const;

		virtual ArgInfo	&setDefaultB(bool defaultV);
		virtual ArgInfo	&setStoreTrue(bool storeTrue = true);

		bool	defaultV;
		bool	storeTrue;  // allow to skip val for bool

	private:
		BoolArg();
};

// -- IntArg -------------------------------------------------------------------
class IntArg : public ArgInfo {
	public:
		explicit IntArg(std::string name);
		virtual ~IntArg();
		IntArg(IntArg const &src);
		IntArg &operator=(IntArg const &rhs);

		virtual void print(std::ostream &out) const;

		virtual ArgInfo	&setDefaultI(int defaultV);
		virtual ArgInfo	&setMinI(int min);
		virtual ArgInfo	&setMaxI(int max);

		int		min;
		int		max;
		int		defaultV;

	private:
		IntArg();
};

// -- FloatArg -----------------------------------------------------------------
class FloatArg : public ArgInfo {
	public:
		explicit FloatArg(std::string name);
		virtual ~FloatArg();
		FloatArg(FloatArg const &src);
		FloatArg &operator=(FloatArg const &rhs);

		virtual void print(std::ostream &out) const;

		virtual ArgInfo	&setDefaultF(float defaultV);
		virtual ArgInfo	&setMinF(float min);
		virtual ArgInfo	&setMaxF(float max);

		float	min;
		float	max;
		float	defaultV;

	private:
		FloatArg();
};

#endif  // ARGINFO_HPP_
