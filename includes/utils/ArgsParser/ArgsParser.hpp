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

typedef AInfoArg *(*BuilderFuncPtr)(ArgsParser *, std::string const);

class ArgsParser {
	public:
		ArgsParser(int ac, char * const *av);
		virtual		~ArgsParser();
		ArgsParser(ArgsParser const &src);
		ArgsParser	&operator=(ArgsParser const &rhs);

		void		usage(bool longUsage = false) const;
		bool		checkOptsAvailability(std::string const &name, std::string
			const &longName, char shortName);
		// create new arg of the specified type, add it to _argsInfos, then return a ref
		AInfoArg	&addArgument(std::string const name, ArgType::Enum const type = ArgType::STRING);
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
			(void)name;
			return "test";
		}
		template <> bool		get<>(std::string const name) const {
			(void)name;
			return true;
		}
		template <> int8_t		get<>(std::string const name) const {
			(void)name;
			return 1;
		}
		template <> int16_t		get<>(std::string const name) const {
			(void)name;
			return 2;
		}
		template <> int32_t		get<>(std::string const name) const {
			(void)name;
			return 3;
		}
		template <> int64_t		get<>(std::string const name) const {
			(void)name;
			return 4;
		}
		template <> uint8_t		get<>(std::string const name) const {
			(void)name;
			return 5;
		}
		template <> uint16_t	get<>(std::string const name) const {
			(void)name;
			return 6;
		}
		template <> uint32_t	get<>(std::string const name) const {
			(void)name;
			return 7;
		}
		template <> uint64_t	get<>(std::string const name) const {
			(void)name;
			return 8;
		}
		template <> float_t		get<>(std::string const name) const {
			(void)name;
			return 9.9;
		}
		template <> double		get<>(std::string const name) const {
			(void)name;
			return 10.10;
		}
		template <> long double	get<>(std::string const name) const {
			(void)name;
			return 11.11;
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

		void	initGetopt();
		ArgsParser();
};

#endif  // ARGSPARSER_HPP_
