#ifndef __TCPSERVER_H__
#define __TCPSERVER_H__

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

#include <iostream>
#include <ctime>

#define MAXCON 200

class ErosTCPServerLinux {
	private:
		int sock;
		unsigned short port;
	public:
		void setPort(unsigned short p);

		void create();
		void bind();
		void listen();
		int accept();
		void close();
		int getSocket();
};
#endif