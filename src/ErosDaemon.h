#ifndef __EROSDAEMON_H__
#define __EROSDAEMON_H__

#include <string>
#include <fstream>

class ErosDaemon {
	public:
		static bool running;

		static void start();
		static void stop();
		static void createPidFile();
		static void handleSingnal(int signal);
};
#endif
