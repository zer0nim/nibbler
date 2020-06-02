#pragma once

#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include <sstream>

#define LOG_COL_EOC		"\x1B[0m"
#define LOG_COL_RED		"\x1B[31m"
#define LOG_COL_GREEN		"\x1B[32m"
#define LOG_COL_YELLOW	"\x1B[33m"
#define LOG_COL_BLUE		"\x1B[34m"
#define LOG_COL_MAGENTA	"\x1B[35m"
#define LOG_COL_CYAN		"\x1B[36m"
#define LOG_COL_WHITE		"\x1B[37m"
#define LOG_COL_F_RED		"\x1B[41m"
#define LOG_COL_F_GREEN	"\x1B[42m"
#define LOG_COL_F_YELLOW	"\x1B[43m"
#define LOG_COL_F_BLUE	"\x1B[44m"
#define LOG_COL_F_MAGENTA	"\x1B[45m"
#define LOG_COL_F_CYAN	"\x1B[46m"
#define LOG_COL_F_WHITE	"\x1B[47m"
#define LOG_COL_CLEAR		"\033[H\033[2J"
#define LOG_COL_BOLD		"\e[1m"
#define COLOR_LIGHT		"\e[2m"
#define LOG_COL_ITALIC	"\e[3m"
#define LOG_COL_ULINE		"\e[4m"

/**
 * @brief All type of level's log
 */
enum	eLoglevel {
	LOGDEBUG, LOGINFO, LOGSUCCESS, LOGWARN, LOGERROR, LOGFATAL, NBLOG
};

#define log_(level, x) { std::stringstream ss; ss << x; logging.log(level, ss.str(), __FILE__, __LINE__); }

#define logDebug(x) log_(LOGDEBUG, x)
#define logInfo(x) log_(LOGINFO, x)
#define logSuccess(x) log_(LOGSUCCESS, x)
#define logWarn(x) log_(LOGWARN, x)
#define logErr(x) log_(LOGERROR, x)
#define logFatal(x) log_(LOGFATAL, x)
#define logErrExit(x) log_(LOGERROR, x)
#define logFatalExit(x) log_(LOGFATAL, x)

/**
 * @brief Logging object
 */
class Logging {
	public:
		Logging();
		Logging(Logging const &src);
		virtual ~Logging();

		Logging &			operator=(Logging const &rhs);

		void				setLoglevel(eLoglevel loglevel);  // don't cout under minLevel
		void				setLogColor(eLoglevel loglevel, std::string const & color);
		void				setPrintFileLine(eLoglevel loglevel, bool printFileLine);
		void				setPrintFileLine(bool printFileLine);

		void				log(eLoglevel level, std::string message, std::string file = "", int line = -1);

		std::string const &	getColor(eLoglevel loglevel) const;
		eLoglevel			getLoglevel() const;

	private:
		std::ofstream	_afile;  ///< The output of the log
		std::string		_colors[NBLOG];  ///< The colors of the logs
		bool			_printFileLine[NBLOG];  ///< The cases we want to print file and lines
		eLoglevel		_loglevel;  ///< Types of level logs
};

extern Logging		logging;
