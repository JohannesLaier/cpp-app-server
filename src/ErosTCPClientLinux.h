#ifndef __TCPCLIENT_H__
#define __TCPCLIENT_H__

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

class ErosTCPClientLinux {
	private:
		int sock;
	
		std::string hostname;
		unsigned short port;
	public:
		ErosTCPClientLinux(int sock);

		void setHost(std::string host);
		void setPort(unsigned short port);

		std::string getHost();
		unsigned short getPort();

		int create();
		void connect();
		void close();

		int sendData(std::string data);
		std::string recvData();
};
#endif