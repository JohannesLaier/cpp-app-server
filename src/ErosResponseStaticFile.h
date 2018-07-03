#ifndef __RESPONSESTATICFILE_H__
#define __RESPONSESTATICFILE_H__

#include <string>
#include <map>

#include "../res/ErosServlet.h"

class ErosResponseStaticFile {
	private:
		std::map<std::string, std::string> mimeTypes;
		std::string getMimeType(const std::string& fileName);
	protected:
		std::string getFile(const std::string& fileName);
};
#endif
