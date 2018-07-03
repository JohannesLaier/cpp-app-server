#ifndef __EROSREQUEST_H__
#define __EROSREQUEST_H__

#include <string>
#include <map>

class ErosRequest {
	private:
		std::map<std::string, std::string> parameter;
	public:
		ErosRequest(std::map<std::string, std::string> param) {
			parameter = param;
		}
		
		std::string getParameter(const std::string& key) {
			return parameter[key];
		}
};

#endif