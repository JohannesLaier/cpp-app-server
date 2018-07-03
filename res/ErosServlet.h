#ifndef __EROSSERVLET_H__
#define __EROSSERVLET_H__

#include "ErosRequest.h"
#include "ErosResponse.h"

#include <string>
#include <map>

class ErosServlet {
	public:
		virtual void doPost(ErosRequest& request, ErosResponse& response) {};
		virtual void doGet(ErosRequest& request, ErosResponse& response) {};
};

#endif