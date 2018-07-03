#ifndef __TCPMULTISERVER_H__
#define __TCPMULTISERVER_H__

#include "ErosTCPServerLinux.h"

#include <sys/types.h>
#include <sys/socket.h>
#include <sys/select.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

#include <iostream>
#include <ctime>

class ErosTCPMultiServerLinux : public ErosTCPServerLinux {
	private:
		int clients[1024];
		int max_clients;
		fd_set readset;

		void erase();
	public:
		void start(int port);
		void close();
		
		virtual void onConnection(int socket) = 0;
		virtual void onMessage(int socket, const std::string& data) = 0;
		virtual void onClose(int socket) = 0;
};
#endif
