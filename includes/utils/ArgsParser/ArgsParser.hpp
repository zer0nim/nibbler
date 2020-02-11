#ifndef ARGSPARSER_HPP_
#define ARGSPARSER_HPP_

#include <getopt.h>
#include <string>
#include <vector>
#include <map>
#include <unordered_map>

#include "AInfoArg.hpp"
#include "TNumberArg.hpp"

class ArgsParser {
	public:
		ArgsParser(int ac, char * const *av);
		virtual		~ArgsParser();
		ArgsParser(ArgsParser const &src);
		ArgsParser	&operator=(ArgsParser const &rhs);

		void		usage(bool longUsage = false) const;
		bool		checkOptsAvailability(std::string name, std::string const &longName, \
			char shortName);
		// create new arg of the specified type, add it to _argsInfos, then return a ref
		AInfoArg	&addArgument(std::string name, ArgType::Enum type = ArgType::STRING);
		void		parseArgs();
		void		setProgDescr(std::string const &progDescr);

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

		void	initGetopt();
		ArgsParser();
};

#endif  // ARGSPARSER_HPP_
