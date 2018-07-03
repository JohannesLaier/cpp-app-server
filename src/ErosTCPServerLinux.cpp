#include "ErosTCPServerLinux.h"

void ErosTCPServerLinux::create() {
	// Neuen Socket vom System anfordern
	sock = socket(AF_INET, SOCK_STREAM, 0);
	if(sock <= 0) {
		throw "Socket Error";
	}
}

void ErosTCPServerLinux::setPort(unsigned short p) {
	port = p;
}

void ErosTCPServerLinux::bind() {
	struct sockaddr_in addr;
	memset(&addr, 0, sizeof(addr));
	
	addr.sin_addr.s_addr = INADDR_ANY;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(port);

	if(sock > 0) {
		if (::bind(sock, (struct sockaddr *) &addr, sizeof(addr)) < 0) { 
             throw "Binding Error";
		}
	}
}

void ErosTCPServerLinux::listen() {
	if(::listen(sock, MAXCON) < 0) {
		throw "Listen ERROR";
	}
}

int ErosTCPServerLinux::accept() {
	int client;
	struct sockaddr_in cli_addr;
    
	socklen_t clientlen = sizeof(cli_addr);
     
    client = ::accept(sock, (struct sockaddr *) &cli_addr, &clientlen);
    if (client < 0) { 
		throw "Accept ERROR";
    } else {
		std::cout << "New Client connected" << std::endl;
    }
    return client;
}

void ErosTCPServerLinux::close() {
	::close(sock);
}

int ErosTCPServerLinux::getSocket() {
	return sock;
}