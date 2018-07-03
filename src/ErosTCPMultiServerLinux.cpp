#include "ErosTCPMultiServerLinux.h"
#include "ErosTCPClientLinux.h"
#include "ErosDaemon.h"


void ErosTCPMultiServerLinux::start(int p) {
	try {
		ErosTCPServerLinux::setPort(p);
		ErosTCPServerLinux::create();
		ErosTCPServerLinux::bind();
		ErosTCPServerLinux::listen();
	} catch(const char* e) {
		std::cout << "ErosTCPMultiServerLinux: " << e << std::endl;
	}
	erase();

	while (ErosDaemon::running) {
		FD_ZERO(&readset);
		FD_SET(ErosTCPServerLinux::getSocket(), &readset);
		
		for (int i=0; i<max_clients; i++) {
			if (clients[i] > 0) {
				FD_SET(clients[i], &readset);
			}
		}
		
		select(max_clients+3, &readset, NULL, NULL, NULL);
		
		if(FD_ISSET(ErosTCPServerLinux::getSocket(), &readset)) {
			int newSocket = ErosTCPServerLinux::accept();
			
			for (int i=0; i<max_clients; i++) {
				if (clients[i] <= 0) {
					clients[i] = newSocket;
					
					FD_SET(newSocket, &readset); // Socket zum set hinzufuegen
					onConnection(newSocket);
					break;
				}
			}
		}
		
		for (int i=0; i<max_clients; i++) {
			if (clients[i] > 0) {
				if (FD_ISSET(clients[i], &readset)) {
					try {
						ErosTCPClientLinux client(clients[i]);
						std::string recvData = client.recvData();

						onMessage(clients[i], recvData);
					} catch(const char* e) {
						std::cout << "ErosTCPMultiServerLinux: " << e << std::endl;

						onClose(clients[i]);

						FD_CLR(clients[i], &readset);
						clients[i] = 0;
					}
				}
			}
		}
	}
}

void ErosTCPMultiServerLinux::erase() {
	max_clients = 1000;
	for (int i=0; i<max_clients; i++) {
		clients[i] = 0;
	}
}

void ErosTCPMultiServerLinux::close() {
	ErosTCPServerLinux::close();
	for (int i=0; i<max_clients; i++) {
		if (clients[i] != 0) {
			ErosTCPClientLinux client(clients[i]);
			client.close();
		}
	}
	erase();
}