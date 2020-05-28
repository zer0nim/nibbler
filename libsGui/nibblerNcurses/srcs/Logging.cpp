#include "Logging.hpp"


Logging		logging;

/**
 * @brief Construct a new Logging:: Logging object
 */
Logging::Logging()
: _loglevel(LOGDEBUG) {
	setLogColor(LOGDEBUG, LOG_COL_WHITE);
	setLogColor(LOGINFO, LOG_COL_WHITE);
	setLogColor(LOGSUCCESS, std::string(LOG_COL_GREEN) + LOG_COL_BOLD);
	setLogColor(LOGWARN, std::string(LOG_COL_YELLOW) + LOG_COL_BOLD);
	setLogColor(LOGERROR, std::string(LOG_COL_RED) + LOG_COL_BOLD);
	setLogColor(LOGFATAL, std::string(LOG_COL_RED) + LOG_COL_BOLD);

	setPrintFileLine(false);

	_afile.open("log.txt", std::ofstream::out | std::ofstream::app);
}

/**
 * @brief Construct a new Logging::Logging object
 *
 * @param src object to copy
 */
Logging::Logging(Logging const &src) {
	*this = src;
}

/**
 * @brief Destroy the Logging::Logging object
 */
Logging::~Logging() {
	_afile.close();
}

/**
 * @brief Copy this object
 *
 * @param rhs The object to copy
 * @return Logging& A reference to the copied object
 */
Logging & Logging::operator=(Logging const &rhs) {
	(void)rhs;
	// if (this != &rhs) {}
	return *this;
}

/**
 * @brief Set log level
 *
 * @param loglevel The level we wand to set
 */
void Logging::setLoglevel(eLoglevel loglevel) {
	_loglevel = loglevel;
}

/**
 * @brief Set level color
 *
 * @param loglevel Which level we want to apply the color
 * @param color The new color
 */
void Logging::setLogColor(eLoglevel loglevel, std::string const & color) {
	_colors[loglevel] = color;
}

/**
 * @brief Set if we want to print the file and line for defined log level
 *
 * @param loglevel Which level we want to apply
 * @param printFileLine The new value for the boolean
 */
void Logging::setPrintFileLine(eLoglevel loglevel, bool printFileLine) {
	_printFileLine[loglevel] = printFileLine;
}
/**
 * @brief Set if we want to print the file and line for all log levels
 *
 * @param printFileLine The new value for the boolean
 */
void Logging::setPrintFileLine(bool printFileLine) {
	for (int level = 0; level < static_cast<int>(NBLOG); level++) {
		setPrintFileLine(static_cast<eLoglevel>(level), printFileLine);
	}
}

/**
 * @brief Make a log
 *
 * @param level The level of the log
 * @param message The message we want to log
 * @param file The file where the log is done
 * @param line The line where the log is called
 */
void	Logging::log(eLoglevel level, std::string message, std::string file, int line) {
	if (level < _loglevel)
		return;
	std::stringstream ss;
	// start logging
	ss << _colors[level];
	if (level == LOGDEBUG) ss << "[DEBUG]";
	else if (level == LOGINFO) ss << "[INFO]";
	else if (level == LOGSUCCESS) ss << "[SUCCESS]";
	else if (level == LOGWARN) ss << "[WARN]";
	else if (level == LOGERROR) ss << "[ERROR]";
	else if (level == LOGFATAL) ss << "[FATAL]";
	if (_printFileLine[level])
		ss << "[" << file << " " << line << "]";
	ss << ": ";
	ss << message;
	ss << LOG_COL_EOC << std::endl;

	_afile << ss.str();
}

/**
 * @brief Get color for a defined level log
 *
 * @param loglevel Which level log
 * @return std::string const& The color
 */
std::string const &	Logging::getColor(eLoglevel loglevel) const { return _colors[loglevel]; }
/**
 * @brief Get level log
 *
 * @return eLoglevel The level log
 */
eLoglevel			Logging::getLoglevel() const { return _loglevel; }
