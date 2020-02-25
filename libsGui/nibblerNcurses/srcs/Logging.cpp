#include "Logging.hpp"


Logging		logging;

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

Logging::Logging(Logging const &src) {
	*this = src;
}

Logging::~Logging() {
	_afile.close();
}

Logging & Logging::operator=(Logging const &rhs) {
	(void)rhs;
	// if (this != &rhs) {}
	return *this;
}

void Logging::setLoglevel(eLoglevel loglevel) {
	_loglevel = loglevel;
}

void Logging::setLogColor(eLoglevel loglevel, std::string const & color) {
	_colors[loglevel] = color;
}

void Logging::setPrintFileLine(eLoglevel loglevel, bool printFileLine) {
	_printFileLine[loglevel] = printFileLine;
}
void Logging::setPrintFileLine(bool printFileLine) {
	for (int level = 0; level < static_cast<int>(NBLOG); level++) {
		setPrintFileLine(static_cast<eLoglevel>(level), printFileLine);
	}
}

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

std::string const &	Logging::getColor(eLoglevel loglevel) const { return _colors[loglevel]; }
eLoglevel			Logging::getLoglevel() const { return _loglevel; }
