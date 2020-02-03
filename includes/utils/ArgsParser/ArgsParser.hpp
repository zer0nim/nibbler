#ifndef ARGSPARSER_HPP_
#define ARGSPARSER_HPP_

#include <getopt.h>
#include <string>
#include <vector>

#include "ArgInfo.hpp"

class ArgsParser {
	public:
		ArgsParser();
		virtual ~ArgsParser();
		ArgsParser(ArgsParser const &src);
		ArgsParser &operator=(ArgsParser const &rhs);

		void	usage() const;
		void	init();
		// create new arg of the specified type, add it to _argsInfos, then return a ref
		ArgInfo	&addArgument(ArgType::Enum type = ArgType::STRING);
		void	parseArgs(int ac, char * const *av);

	private:
		std::string					_opts;
		std::vector<struct option>	_longOpts;
		std::vector<ArgInfo *>		_argsInfos;
};

#endif  // ARGSPARSER_HPP_
