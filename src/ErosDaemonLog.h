#ifndef __EROSDAEMONLOG_H__
#define __EROSDAEMONLOG_H__

#include <string>
#include <algorithm>
#include <functional>

class ErosDaemonLog {
	public:
		ErosDaemonLog();
		~ErosDaemonLog();
		ErosDaemonLog& operator <<(const std::string& data);
};
#endif
