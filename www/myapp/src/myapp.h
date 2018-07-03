#ifndef __myapp_H__
#define __myapp_H__

#include "../res/ErosServlet.h"
#include "../res/ErosRequest.h"
#include "../res/ErosResponse.h"

#include <string>

class myapp : public ErosServlet {
	public:
		void doPost(ErosRequest& request, ErosResponse& response);
		void doGet(ErosRequest& request, ErosResponse& response);
};

extern "C" myapp* create_object() {
  return new myapp;
}

extern "C" void destroy_object( myapp* object ) {
  delete object;
}

#endif

