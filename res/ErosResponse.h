#ifndef __EROSRESPONSE_H__
#define __EROSRESPONSE_H__

#include <iterator>
#include <sstream>
#include <string>
#include <map>

enum HTTPSTATUS {
	_200 = 200, _404 = 404
};

class ErosResponse {
	private:
		std::map<HTTPSTATUS, std::string> statusCodes;
		std::map<std::string, std::string> header;

		HTTPSTATUS statusCode;

		int versionMajor;
		int versionMinor;
		bool keepAlive;

		std::string content;
	public:
		ErosResponse() {
			// Fill Data
			statusCodes[_200] = "OK";
			statusCodes[_404] = "Not Found";

			statusCode = _200;
			versionMajor = 1;
			versionMinor = 1;
			keepAlive = false;
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
			statusCode = status;
		}

		std::string getHeader(const std::string& key) {
			return header[key];
		}

		std::string getContent() {
			return content;
		}

		std::string parse() {
			std::stringstream stream;
			stream << "HTTP/" << versionMajor << "." << versionMinor
				   << " " << statusCode << " " << statusCodes[statusCode] << "\n";

			for (std::map<std::string, std::string>::iterator it = header.begin(); it != header.end(); it++) {
				stream << it->first << ": " << it->second << "\n";
			}

			stream << "\n" << content << "\n";
			return stream.str();
		}
};

#endif
