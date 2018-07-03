#include "ErosDaemon.h"
#include "ErosConfig.h"


#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <signal.h>

bool ErosDaemon::running = true;

void ErosDaemon::start() {
	signal(SIGINT, handleSingnal);
	signal(SIGTERM, handleSingnal);
	signal(SIGHUP, handleSingnal);
	signal(SIGPIPE, SIG_IGN);

	pid_t pid = fork();
	
	if (pid < 0) {
		exit(EXIT_FAILURE);
	}
	
	if (pid > 0) {
		exit(EXIT_SUCCESS);
	}

	pid_t sid = setsid();
	if (sid < 0) {
		exit(EXIT_FAILURE);
	}

	if ((chdir(CONFIG_DIRECTORY)) < 0) {
		exit(EXIT_FAILURE);
	}

	umask(0);
	
	createPidFile();
	
	for (int i = sysconf(_SC_OPEN_MAX); i > 0; i--) {
		close(i);
	}
}

void ErosDaemon::handleSingnal(int signal) {
	switch(signal) {
		case SIGHUP:
			break;
		case SIGINT:
		case SIGTERM:
			stop();
			exit(EXIT_SUCCESS);
			break;
		default:
			break;
	}
}

void ErosDaemon::createPidFile() {
	std::ofstream out;
	out.open(CONFIG_PID_FILE, std::ios::out);
	if (out.is_open()) {
		out << getpid();
	}
	out.close();
}

void ErosDaemon::stop() {
	running = false;
	unlink(CONFIG_PID_FILE);
}
