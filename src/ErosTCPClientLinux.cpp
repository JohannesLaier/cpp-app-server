#include "ErosTCPClientLinux.h"

#include <iostream>
#include <string>

using namespace std;
//ErosTCPClientLinux::ErosTCPClientLinux(std::string host, unsigned short p) {
//	hostname = host;
//	port = p;
//  bigContent = false;
//	startWinsock();
//	downloadFinished = false;
//}

ErosTCPClientLinux::ErosTCPClientLinux(int s) {
	sock = s;
}

void ErosTCPClientLinux::connect() {
	struct sockaddr_in addr;
	struct hostent *host_info;

	memset(&addr, 0, sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_port = htons(port);

	if(inet_addr(hostname.c_str()) != INADDR_NONE) {
		addr.sin_addr.s_addr = inet_addr(hostname.c_str()); //hostname beinhaltet eine valide IP
	} else {
		host_info = gethostbyname(hostname.c_str()); // Hostname nach IP aufl�sen
		if (NULL == host_info) {
			std::cout << "Unbekannter Server" << std::endl;
			throw "Unbekannter Server";
		} else {
			memcpy((char *)&addr.sin_addr, host_info->h_addr, host_info->h_length);
		}
	}
	
	if (::connect(sock, (struct sockaddr *) &addr, sizeof (addr)) < 0) {
		throw "Connect Error";
	}
}

int ErosTCPClientLinux::create() {
	// Neuen Socket vom System anfordern
	sock = socket(AF_INET, SOCK_STREAM, 0);
	if(sock <= 0) {
		throw "Socket Error";
	}
	return sock;
}

void ErosTCPClientLinux::close() {
	::close(sock);
}

int ErosTCPClientLinux::sendData(std::string data) {
	int state = write(sock, data.c_str(), data.size());
	if (state  < 0) {
		throw "Send Error";
	}
	std::cout << "Send: " << data << std::endl;
	return state;
}

std::string ErosTCPClientLinux::recvData() {
	char *buf = new char[1000000]; //Wird nur wegen Downloads im Heap Allocoiert
	memset(buf, 0, 1000000);
	std::string recvData;
	int recvLength = 0;

	do {
		recvLength = read(sock, buf, 1000000);
		if(recvLength > 0) {
			recvData = buf;
			delete[] buf;
			std::cout << "Recv: " << recvData << std::endl;
			return recvData;
		} else if(recvLength < 0) {
			throw "Connection Error";
		} else if (recvLength == 0) {
			close(); // Connection beenden
		}
	} while(recvLength <= 0);
	throw "Connection Error";
}

void ErosTCPClientLinux::setHost(std::string host) {
	hostname = host;
}

void ErosTCPClientLinux::setPort(unsigned short p) {
	port = p;
}

unsigned short ErosTCPClientLinux::getPort() {
	return port;
}

std::string ErosTCPClientLinux::getHost() {
	return hostname;
}