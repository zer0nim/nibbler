#ifndef ARGSPARSER_HPP_
#define ARGSPARSER_HPP_

#include <getopt.h>
#include <string>
#include <vector>
#include <array>
#include <map>
#include <unordered_map>

#include "AInfoArg.hpp"
#include "TNumberArg.hpp"

typedef AInfoArg *(*BuilderFuncPtr)(ArgsParser *, std::string const &, std::string const &, char);

class ArgsParser {
	public:
		ArgsParser(int ac, char * const *av);
		virtual		~ArgsParser();
		ArgsParser(ArgsParser const &src);
		ArgsParser	&operator=(ArgsParser const &rhs);

		void		usage(bool longUsage = false) const;
		void		checkOptsAvailability(std::string const &name, std::string const &longName,
			char shortName);
		// create new arg of the specified type, add it to _argsInfos, then return a ref
		AInfoArg	&addArgument(std::string const name, ArgType::Enum const type = ArgType::STRING);
		// optionals arguments version
		AInfoArg	&addArgument(std::string const name, ArgType::Enum const type,
			std::string const longName, char shortName = A_NO_NAME);
		// idem but easier to set only shortName
		AInfoArg	&addArgument(std::string const name, ArgType::Enum const type,
			char shortName, std::string const longName = std::string());
		void		parseArgs();
		void		setProgDescr(std::string const &progDescr);

		// -- get template to return value -------------------------------------
		// willingly unimplemented the default template
		template <typename T> T get(std::string const name) const {
			(void)name;
			// `unimplemented_function` identifier should be undefined
			T::unimplemented_function;
		}

		template <> std::string	get<>(std::string const name) const {
			// get the value
			std::pair<std::string, bool>	val = reinterpret_cast<
				StringArg *>(_get(name, ArgType::STRING))->getVal();
			// value not set
			if (!val.second) {
				throw ArgsParserException(std::string("argument \"" + name +
					"\": value is empty").c_str());
			}
			return val.first;
		}
		template <> bool		get<>(std::string const name) const {
			// get the value
			std::pair<bool, bool>	val = reinterpret_cast<
				BoolArg *>(_get(name, ArgType::BOOL))->getVal();
			// value not set
			if (!val.second) {
				throw ArgsParserException(std::string("argument \"" + name +
					"\": value is empty").c_str());
			}
			return val.first;
		}
		template <> int8_t		get<>(std::string const name) const {
			// get the value
			std::pair<int8_t, bool>	val = reinterpret_cast<
				NumberArg<int8_t> *>(_get(name, ArgType::INT8))->getVal();
			// value not set
			if (!val.second) {
				throw ArgsParserException(std::string("argument \"" + name +
					"\": value is empty").c_str());
			}
			return val.first;
		}
		template <> int16_t		get<>(std::string const name) const {
			// get the value
			std::pair<int16_t, bool>	val = reinterpret_cast<
				NumberArg<int16_t> *>(_get(name, ArgType::INT16))->getVal();
			// value not set
			if (!val.second) {
				throw ArgsParserException(std::string("argument \"" + name +
					"\": value is empty").c_str());
			}
			return val.first;
		}
		template <> int32_t		get<>(std::string const name) const {
			// get the value
			std::pair<int32_t, bool>	val = reinterpret_cast<
				NumberArg<int32_t> *>(_get(name, ArgType::INT32))->getVal();
			// value not set
			if (!val.second) {
				throw ArgsParserException(std::string("argument \"" + name +
					"\": value is empty").c_str());
			}
			return val.first;
		}
		template <> int64_t		get<>(std::string const name) const {
			// get the value
			std::pair<int64_t, bool>	val = reinterpret_cast<
				NumberArg<int64_t> *>(_get(name, ArgType::INT64))->getVal();
			// value not set
			if (!val.second) {
				throw ArgsParserException(std::string("argument \"" + name +
					"\": value is empty").c_str());
			}
			return val.first;
		}
		template <> uint8_t		get<>(std::string const name) const {
			// get the value
			std::pair<uint8_t, bool>	val = reinterpret_cast<
				NumberArg<uint8_t> *>(_get(name, ArgType::UINT8))->getVal();
			// value not set
			if (!val.second) {
				throw ArgsParserException(std::string("argument \"" + name +
					"\": value is empty").c_str());
			}
			return val.first;
		}
		template <> uint16_t	get<>(std::string const name) const {
			// get the value
			std::pair<uint16_t, bool>	val = reinterpret_cast<
				NumberArg<uint16_t> *>(_get(name, ArgType::UINT16))->getVal();
			// value not set
			if (!val.second) {
				throw ArgsParserException(std::string("argument \"" + name +
					"\": value is empty").c_str());
			}
			return val.first;
		}
		template <> uint32_t	get<>(std::string const name) const {
			// get the value
			std::pair<uint32_t, bool>	val = reinterpret_cast<
				NumberArg<uint32_t> *>(_get(name, ArgType::UINT32))->getVal();
			// value not set
			if (!val.second) {
				throw ArgsParserException(std::string("argument \"" + name +
					"\": value is empty").c_str());
			}
			return val.first;
		}
		template <> uint64_t	get<>(std::string const name) const {
			// get the value
			std::pair<uint64_t, bool>	val = reinterpret_cast<
				NumberArg<uint64_t> *>(_get(name, ArgType::UINT64))->getVal();
			// value not set
			if (!val.second) {
				throw ArgsParserException(std::string("argument \"" + name +
					"\": value is empty").c_str());
			}
			return val.first;
		}
		template <> float_t		get<>(std::string const name) const {
			// get the value
			std::pair<float_t, bool>	val = reinterpret_cast<
				NumberArg<float_t> *>(_get(name, ArgType::FLOAT))->getVal();
			// value not set
			if (!val.second) {
				throw ArgsParserException(std::string("argument \"" + name +
					"\": value is empty").c_str());
			}
			return val.first;
		}
		template <> double		get<>(std::string const name) const {
			// get the value
			std::pair<double, bool>	val = reinterpret_cast<
				NumberArg<double> *>(_get(name, ArgType::DOUBLE))->getVal();
			// value not set
			if (!val.second) {
				throw ArgsParserException(std::string("argument \"" + name +
					"\": value is empty").c_str());
			}
			return val.first;
		}
		template <> long double	get<>(std::string const name) const {
			// get the value
			std::pair<long double, bool>	val = reinterpret_cast<
				NumberArg<long double> *>(_get(name, ArgType::L_DOUBLE))->getVal();
			// value not set
			if (!val.second) {
				throw ArgsParserException(std::string("argument \"" + name +
					"\": value is empty").c_str());
			}
			return val.first;
		}

		// -- exceptions -------------------------------------------------------
		class ArgsParserException : public std::runtime_error {
			public:
				ArgsParserException();
				explicit ArgsParserException(const char* what_arg);
		};
		class ArgsParserUsage : public std::runtime_error {
			public:
				ArgsParserUsage();
		};

	private:
		int							_ac;
		char * const				*_av;
		std::string					_progDescr;
		std::string					_opts;
		std::vector<struct option>	_longOpts;

		std::vector<AInfoArg *>						_argsInfos;
		std::unordered_map<std::string, uint32_t>	_argsId;
		std::unordered_map<char, uint32_t>			_sOptArgsId;
		std::unordered_map<std::string, uint32_t>	_lOptArgsId;

		static std::array<BuilderFuncPtr, 13> const	_builders;

		void		_initGetopt();
		AInfoArg	*_get(std::string const name, ArgType::Enum const type) const;
		void		_strReplace(std::string &str, std::string search, std::string replace);
		ArgsParser();
};

#endif  // ARGSPARSER_HPP_
