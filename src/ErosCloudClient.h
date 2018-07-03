#ifndef __CLIENT_H__
#define __CLIENT_H__

#include "ErosTCPMultiServerLinux.h"
#include "ErosTCPClientLinux.h"
#include "ErosResponseError.h"
#include "ErosResponseRunTime.h"
#include "ErosResponseStaticFile.h"


#include "ErosString.h"
#include "ErosCast.h"
#include <map>

class ErosCloudClient : public ErosTCPMultiServerLinux, public ErosResponseRunTime, public ErosResponseStaticFile, public ErosResponseError {
	private:
		int socket;
	public:
		void onConnection(int sock);
		void onMessage(int sock, const std::string& message);
		void onClose(int sock);

		void handleRequest(const std::string &data);
		void sendResponse(const std::string &response);
};
#endif
