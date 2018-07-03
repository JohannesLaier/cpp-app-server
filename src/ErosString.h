#ifndef __EROSSTRING_H__
#define __EROSSTRING_H__

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <functional>

using namespace std;

class ErosString {
	private:
		std::string stringData;
	public:
		//r-value und l-value �berladen
		ErosString& operator = (const std::string s);
		operator std::string();

		//== und != �berladen
		bool operator==(const std::string s);
		bool operator!=(const std::string s);

		ErosString(std::string data);
		~ErosString(void);

		void setData(std::string data);
		std::string getData();

		std::string getDataBefor(std::string data);
		std::string getDataAfter(std::string data);
		std::string replace(std::string from, std::string to);
		std::string toUpper();
		std::string toLower();
		bool contains(std::string data);
		std::vector<std::string> splitString(const char *sep);
		int length();
};
#endif