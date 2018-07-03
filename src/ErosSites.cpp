#include "ErosSites.h"
#include "ErosConfig.h"
#include "ErosCloudClient.h"

#include <dirent.h>

std::vector<pid_t>  ErosSites::childrenProcesses;

std::string ErosSites::configFile;

void ErosSites::start() {
	startSites();
}

void ErosSites::startSites() {
	std::vector<std::string> childrenConfigs = getSites();
	for (unsigned int i = 0; i < childrenConfigs.size(); i++) {
		configFile = childrenConfigs[i];

		pid_t pid = fork();
		if (pid > 0) {
			childrenProcesses.push_back(pid);
		} else {
			handleSite();
			break;
		}
	}
}

void ErosSites::handleSite() {
	// Load Config
	ErosConfig::load(configFile);
	
	// Start Client Server
	ErosCloudClient mserver;
	mserver.start(ErosConfig::port);
}

std::vector<std::string> ErosSites::getSites() {
	std::vector<std::string> childrenConfigs;

	struct dirent *direntry;
	DIR* dir = opendir(CONFIG_DIRECTORY);
	while ((direntry = readdir(dir))) {
		std::string entry(direntry->d_name);
		if (entry != "." && entry != "..") {
			childrenConfigs.push_back(CONFIG_DIRECTORY + entry);
		}
	}
	closedir(dir);

	return childrenConfigs;
}