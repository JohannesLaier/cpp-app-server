#include "ErosResponseRunTime.h"

#include <dlfcn.h>
#include <string>

#include <iostream>

std::string ErosResponseRunTime::callLibrary(ErosRequest& request) {
	ErosResponse response;
	
	void* handle = dlopen(request.getPath().c_str(), RTLD_LAZY);
	if (handle != NULL) {
		ErosServlet* (*create)();
		void (*destroy)(ErosServlet*);

		create = (ErosServlet* (*)()) dlsym(handle, "create_object");
		destroy = (void (*)(ErosServlet*)) dlsym(handle, "destroy_object");

		ErosServlet* nServlet = (ErosServlet*) create();

		if (request.getMethod() == "GET") {
			nServlet->doGet(request, response);
		}

		if (request.getMethod() == "POST") {
			nServlet->doPost(request, response);
		}
		
		destroy(nServlet);
	}
	dlclose(handle);
	return response.parse();
}
