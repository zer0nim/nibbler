#ifndef ARGINFO_HPP_
#define ARGINFO_HPP_

#include <string>

namespace ArgType {
	enum Enum {
		STRING,
		BOOL,
		INT,
		FLOAT,
	};
}

// -- ArgInfo ------------------------------------------------------------------
class ArgInfo {
	public:
		ArgInfo();
		virtual ~ArgInfo();
		ArgInfo(ArgInfo const &src);
		ArgInfo &operator=(ArgInfo const &rhs);

		ArgType::Enum	type;
		std::string		shortName;
		std::string		longName;
		std::string		help;
		bool			required;

	private:
};

// -- StringArg ----------------------------------------------------------------
class StringArg: ArgInfo {
	public:
		StringArg();
		virtual ~StringArg();
		StringArg(StringArg const &src);
		StringArg &operator=(StringArg const &rhs);

		int				min;  // min string lenght
		int				max;  // max string lenght
		std::string		defaultV;
	private:
};

// -- BoolArg ------------------------------------------------------------------
class BoolArg: ArgInfo {
	public:
		BoolArg();
		virtual ~BoolArg();
		BoolArg(BoolArg const &src);
		BoolArg &operator=(BoolArg const &rhs);

		bool	defaultV;
		bool	storeTrue;  // allow to skip val for bool
	private:
};

// -- IntArg -------------------------------------------------------------------
class IntArg: ArgInfo {
	public:
		IntArg();
		virtual ~IntArg();
		IntArg(IntArg const &src);
		IntArg &operator=(IntArg const &rhs);

		int		min;
		int		max;
		int		defaultV;
	private:
};

// -- FloatArg -----------------------------------------------------------------
class FloatArg: ArgInfo {
	public:
		FloatArg();
		virtual ~FloatArg();
		FloatArg(FloatArg const &src);
		FloatArg &operator=(FloatArg const &rhs);

		float	min;
		float	max;
		float	defaultV;
	private:
};

#endif  // ARGINFO_HPP_
