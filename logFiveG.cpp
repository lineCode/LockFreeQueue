#include "logFiveG.hh"

std::ostream & operator<<(std::ostream &os, LogFiveG const &m) {
    os << "[" << m.severity() << "," << m.theLog_ << "]";
    return os;
}

std::string LogFiveG::severity() const {
    switch (this->theLogSeverity_)
    {
        case LOG_EMERG:
            return "EMER";
        case LOG_ALERT:
            return "ALERT";
        case LOG_CRIT:
            return "CRIT";            
        case LOG_ERR:
            return "ERROR";
        case LOG_WARNING:
            return "WARNING";
        case LOG_NOTICE:
            return "NOTICE";
        case LOG_INFO:
            return "INFO";
    }
    return "DEBUG";
}

void LogFiveG::setLog (unsigned char logSeverity, const std::string &log){
    this->theLogSeverity_ = logSeverity;
    this->theLog_ = log;
}
