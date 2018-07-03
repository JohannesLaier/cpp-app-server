#ifndef __RESPONSERUNTIME_H__
#define __RESPONSERUNTIME_H__

#include <string>

#include "ErosRequestParse.h"
#include "../res/ErosRequest.h"
#include "../res/ErosServlet.h"

class ErosResponseRunTime {
	protected:
		std::string callLibrary(ErosRequest& request);
};
#endif
