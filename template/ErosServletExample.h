#ifndef __EROSSERVLETEXAMPLE_H__
#define __EROSSERVLETEXAMPLE_H__

#include "../res/ErosServlet.h"
#include "../res/ErosRequest.h"
#include "../res/ErosResponse.h"

#include <string>

class ErosServletExample : public ErosServlet {
	public:
		void doPost(ErosRequest& request, ErosResponse& response);
		void doGet(ErosRequest& request, ErosResponse& response);
};

extern "C" ErosServletExample* create_object() {
  return new ErosServletExample;
}

extern "C" void destroy_object( ErosServletExample* object ) {
  delete object;
}

#endif

