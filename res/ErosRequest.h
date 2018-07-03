#ifndef __EROSREQUEST_H__
#define __EROSREQUEST_H__

#include <string>
#include <vector>
#include <map>

class ErosRequest {

	public:
		struct HeaderItem
		{
			std::string name;
			std::string value;
		};

	private:
		int versionMajor;
		int versionMinor;
		bool keepAlive;

		std::string path;
		std::string method;
		std::string content;

		std::vector<HeaderItem> headers;

		std::map<std::string, std::string> parameter;

	public:
		std::string getParameter(const std::string& key) {
			return parameter[key];
		}

		void setVersionMajor(int version) {
			versionMajor = version;
		}

		void setVersionMinor(int version) {
			versionMinor = version;
		}

		void setPath(std::string p) {
			path = p;
		}

		void setMethod(std::string m) {
			method = m;
		}

		void setContent(std::string c) {
			content = c;
		}

		void setKeepAlive(bool ka) {
			keepAlive = ka;
		}

		int getVersionMajor() {
			return versionMajor;
		}

		int getVersionMinor() {
			return versionMinor;
		}

		std::string getPath() {
			return path;
		}

        std::string getMethod() {
            return method;
        }

		std::string getContent() {
			return content;
		}

		std::vector<HeaderItem>& getHeaders() {
			return headers;
		}
};

#endif
