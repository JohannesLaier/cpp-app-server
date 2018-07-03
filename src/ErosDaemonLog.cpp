#include "ErosDaemonLog.h"
#include <syslog.h>

ErosDaemonLog::ErosDaemonLog() {
	openlog("ErosCloud", LOG_PID | LOG_ODELAY, LOG_LOCAL1);
}

ErosDaemonLog& ErosDaemonLog::operator <<(const std::string& data) {
	syslog(LOG_INFO, data.c_str());
	return *this;
}

ErosDaemonLog::~ErosDaemonLog() {
	closelog();
}
