#ifndef ARGSPARSER_HPP_
#define ARGSPARSER_HPP_

#include <getopt.h>
#include <string>
#include <vector>
#include <set>

#include "ArgInfo.hpp"

class ArgsParser {
	public:
		ArgsParser(int ac, char * const *av);
		virtual ~ArgsParser();
		ArgsParser(ArgsParser const &src);
		ArgsParser &operator=(ArgsParser const &rhs);

		void	usage() const;
		bool	checkOptsAvailability(std::string const &longName, char shortName);
		// create new arg of the specified type, add it to _argsInfos, then return a ref
		ArgInfo	&addArgument(std::string name, ArgType::Enum type = ArgType::STRING);
		void	parseArgs();
		void	setProgDescr(std::string const &progDescr);

		class ArgsParserException : public std::runtime_error {
			public:
				ArgsParserException();
				explicit ArgsParserException(const char* what_arg);
		};

	private:
		int							_ac;
		char * const				*_av;
		std::string					_progDescr;
		std::string					_opts;
		std::vector<struct option>	_longOpts;
		std::set<ArgInfo *, ArgInfoPtrComp>	_argsInfos;

		void	init();
		ArgsParser();
};

#endif  // ARGSPARSER_HPP_
