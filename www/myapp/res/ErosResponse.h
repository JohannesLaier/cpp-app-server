#ifndef __EROSRESPONSE_H__
#define __EROSRESPONSE_H__

#include <sstream>
#include <string>
#include <map>

enum HTTPSTATUS {
	_200 = 1, _404
};

class ErosResponse {
	private:
		std::map<HTTPSTATUS, std::string> statusCodes;
		std::map<std::string, std::string> header;
		std::string content;
		HTTPSTATUS httpStatus;
	public:
		ErosResponse() {
			// Fill Data
			statusCodes[_200] = "200 OK";
			statusCodes[_404] = "404 Not Found";
		
			httpStatus = _200;
			header["Content-Type"] = "text/html";
		}

		void setHeader(const std::string& key, const std::string& value) {
			header[key] = value;
		}

		void setContent(const std::string& c) {
			content = c;
		}
		
		void setContent(const std::istream& in) {
			std::stringstream stream;
			stream << in.rdbuf();
			content = stream.str();
		}
		
		void setStatus(HTTPSTATUS status) {
			httpStatus = status;
		}

		std::string getHeader(const std::string& key) {
			return header[key];
		}

		std::string getContent(){
			return content;
		}

		std::string parse() {
			std::string responseString = "HTTP/1.1 " + statusCodes[httpStatus] + "\r\n";
			for (std::map<std::string, std::string>::iterator it = header.begin(); it != header.end(); ++it) {
				responseString += it->first;
				responseString += ": ";
				responseString += it->second;
				responseString += "\r\n";
			}
			responseString += "\r\n\r\n";
			responseString += content;
			responseString += "\r\n\r\n";
			return responseString;
		}
};

#endif
