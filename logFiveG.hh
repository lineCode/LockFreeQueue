#ifndef __LOG_FIVEG__
#define __LOG_FIVEG__

#include "sys/syslog.h"
#include <iostream>
#include <string>

class LogFiveG {
    public:
        LogFiveG () = default;  
        LogFiveG (unsigned char logSeverity, const std::string &log) : theLogSeverity_(logSeverity), theLog_(log) {};  
        LogFiveG(const LogFiveG&) = default;

        ~LogFiveG() = default;

        LogFiveG& operator=(const LogFiveG& obj)  = default;
        
        void setLog (unsigned char logSeverity, const std::string &log);
        std::string severity() const;
        friend std::ostream& operator<<(std::ostream&, const LogFiveG&);
    private:
        unsigned char theLogSeverity_;
        std::string theLog_;
};
#endif //__LOG_FIVEG__