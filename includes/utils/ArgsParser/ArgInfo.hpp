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

		ArgInfo	&setOptional(std::string longName, char shortName = A_NO_NAME);
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
		virtual ArgInfo	&setMinLength(uint32_t min);
		virtual ArgInfo	&setMaxLength(uint32_t max);

		uint32_t		min;  // min string lenght
		uint32_t		max;  // max string lenght
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

// -- Int32Arg -------------------------------------------------------------------
class Int32Arg : public ArgInfo {
	public:
		explicit Int32Arg(std::string name);
		virtual ~Int32Arg();
		Int32Arg(Int32Arg const &src);
		Int32Arg &operator=(Int32Arg const &rhs);

		virtual void print(std::ostream &out) const;

		virtual ArgInfo	&setDefaultI32(int32_t defaultV);
		virtual ArgInfo	&setMinI32(int32_t min);
		virtual ArgInfo	&setMaxI32(int32_t max);

		int32_t	min;
		int32_t	max;
		int32_t	defaultV;

	private:
		Int32Arg();
};

// -- Int64Arg -------------------------------------------------------------------
class Int64Arg : public ArgInfo {
	public:
		explicit Int64Arg(std::string name);
		virtual ~Int64Arg();
		Int64Arg(Int64Arg const &src);
		Int64Arg &operator=(Int64Arg const &rhs);

		virtual void print(std::ostream &out) const;

		virtual ArgInfo	&setDefaultI64(int64_t defaultV);
		virtual ArgInfo	&setMinI64(int64_t min);
		virtual ArgInfo	&setMaxI64(int64_t max);

		int64_t	min;
		int64_t	max;
		int64_t	defaultV;

	private:
		Int64Arg();
};

// -- UInt32Arg -------------------------------------------------------------------
class UInt32Arg : public ArgInfo {
	public:
		explicit UInt32Arg(std::string name);
		virtual ~UInt32Arg();
		UInt32Arg(UInt32Arg const &src);
		UInt32Arg &operator=(UInt32Arg const &rhs);

		virtual void print(std::ostream &out) const;

		virtual ArgInfo	&setDefaultUI32(uint32_t defaultV);
		virtual ArgInfo	&setMinUI32(uint32_t min);
		virtual ArgInfo	&setMaxUI32(uint32_t max);

		uint32_t	min;
		uint32_t	max;
		uint32_t	defaultV;

	private:
		UInt32Arg();
};

// -- UInt64Arg -------------------------------------------------------------------
class UInt64Arg : public ArgInfo {
	public:
		explicit UInt64Arg(std::string name);
		virtual ~UInt64Arg();
		UInt64Arg(UInt64Arg const &src);
		UInt64Arg &operator=(UInt64Arg const &rhs);

		virtual void print(std::ostream &out) const;

		virtual ArgInfo	&setDefaultUI64(uint64_t defaultV);
		virtual ArgInfo	&setMinUI64(uint64_t min);
		virtual ArgInfo	&setMaxUI64(uint64_t max);

		uint64_t	min;
		uint64_t	max;
		uint64_t	defaultV;

	private:
		UInt64Arg();
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
