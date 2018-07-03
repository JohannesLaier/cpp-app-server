#ifndef __EROSSITES_H__
#define __EROSSITES_H__

#include <string>
#include <vector>
#include <map>

#include <sys/types.h>
#include <unistd.h>

class ErosSites {
	public:
		// Parrent Process
		static std::vector<pid_t> childrenProcesses;

		static void start();
		static void startSites();
		static std::vector<std::string> getSites();

		// Child Prosesses
		static std::string configFile;
		static void handleSite();
};
#endif
