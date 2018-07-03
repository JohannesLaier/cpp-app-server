#include "ErosCloudClient.h"
#include "ErosString.h"
#include "ErosConfig.h"
#include "ErosString.h"
#include "ErosFile.h"
#include "ErosCast.h"

#include <iostream>
#include <string>

void ErosCloudClient::onConnection(int sock) {}

void ErosCloudClient::onClose(int sock) {}

void ErosCloudClient::onMessage(int sock, const std::string& message) {
	socket = sock;
	handleRequest(message);
}

void ErosCloudClient::sendResponse(const std::string &response) {
	ErosTCPClientLinux client(socket);
	client.sendData(response);
	client.close();
}

void ErosCloudClient::handleRequest(const std::string &data) {
	ErosRequest req;

	ErosRequestParse parser;
	parser.parse(req, data);

	std::string path = req.getPath();
	if (path == "/") {
		ErosFile nFile(ErosConfig::workspace + "/index.so");
		if (nFile.exist()) {
			path = "/index.so";
		} else {
			path = "/index.html";
		}
	}

	// File inclution vuln entfernt
	ErosString nPath(path);
	nPath.replace("../", "");
	
	path = ErosConfig::workspace + nPath.getData();
	
	ErosFile nFile(path);
	if (!nFile.exist()) {
		sendResponse(get404());
		return;
	}

	if (nFile.extension() == "so") {
		sendResponse(callLibrary(req));
	} else {
		sendResponse(getFile(path));
	}
}