#include "ErosSites.h"
#include "ErosDaemon.h"
#include "ErosDaemonLog.h"

int main(int argc, char** argv) {;	
	// Deamon Starten
	ErosDaemon::start();

	// Sites Starten
	ErosSites::start();
	
	return 0;
}
