#ifndef __EROSCONFIG_H__
#define __EROSCONFIG_H__

#define CONFIG_NAME "eroscloud"
#define CONFIG_PID_FILE "/run/eroscloud.pid"
#define CONFIG_DIRECTORY "/etc/eroscloud/sites-enabled/"

#include <fstream>
#include <sstream>
#include <string>

class ErosConfig {
	public:
		static std::string workspace;
		static unsigned short port;

		static void load(const std::string& file);
		static void parse(std::ifstream& in);	
};

#endif
