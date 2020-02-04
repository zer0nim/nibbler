#ifndef ARGSPARSER_HPP_
#define ARGSPARSER_HPP_

#include <getopt.h>
#include <string>
#include <vector>

#include "ArgInfo.hpp"

class ArgsParser {
	public:
		ArgsParser(int ac, char * const *av);
		virtual ~ArgsParser();
		ArgsParser(ArgsParser const &src);
		ArgsParser &operator=(ArgsParser const &rhs);

		void	usage() const;
		void	init();
		// create new arg of the specified type, add it to _argsInfos, then return a ref
		ArgInfo	&addArgument(std::string name, ArgType::Enum type = ArgType::STRING);
		void	parseArgs();

	private:
		int							_ac;
		char * const				*_av;
		std::string					_opts;
		std::vector<struct option>	_longOpts;
		std::vector<ArgInfo *>		_argsInfos;

		ArgsParser();
};

#endif  // ARGSPARSER_HPP_
