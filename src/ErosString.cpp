#include "ErosString.h"

using namespace std;

ErosString::ErosString(std::string data) {
	stringData = data;
}

ErosString::~ErosString(void)
{
}

ErosString& ErosString::operator=(const std::string s) {
	setData(s);
	return *this;
}

ErosString::operator std::string() {
	return stringData;
}

bool ErosString::operator==(const std::string s) {
	if(s.compare(stringData) == 0) {
		return true;
	}
	return false;
}

bool ErosString::operator!=(const std::string s) {
	if(s.compare(stringData) != 0) {
		return true;
	}
	return false;
}

void ErosString::setData(std::string data) {
	stringData = data;
}


std::string ErosString::getData() {
	return stringData;
}

std::string ErosString::getDataAfter(std::string data) {
	std::string::size_type found;
	found = stringData.find(data);
	if(found != std::string::npos) {
		stringData.replace(0, (found + data.length()), "");
	}
	return stringData;
}

std::string ErosString::getDataBefor(std::string data) {
	std::string::size_type found;
	found = stringData.find(data);
	if(found != std::string::npos) {

		stringData.replace(found, stringData.length(), "");
		return stringData;
	}
	return data;
}

std::string ErosString::replace(std::string from, std::string to) {
	std::string::size_type found;
	do {
		found = stringData.find(from);
		if (std::string::npos != found) {
			stringData.replace(found, from.length(), to);
		}
	} while (std::string::npos != found);
	return stringData;
}

std::vector<std::string> ErosString::splitString(const char *sep) {
	std::string str = stringData;
	unsigned int max_tokens = 0;

	std::vector<std::string> vals;
       
	if (!str.length() || str.length() <= 0) {
		return vals;
	}

	std::string::size_type start = str.find_first_not_of(" \n\t");
	if (start == std::string::npos) {
		return vals;
	}

	std::string::size_type stop;
	unsigned int tokens = 0;

	for (unsigned int i = 0; (max_tokens == 0) || (i < max_tokens); ++i) {
		if (max_tokens && ((i + 1) == max_tokens)) {
			stop = str.size();
		} else {
			stop = str.find_first_of(sep, start);
		}

		if (stop != std::string::npos) {
			if (stop > start) {
				vals.push_back(str.substr(start, stop - start));
				++tokens;
			}
		} else if (start < str.size()) {
			vals.push_back(str.substr(start, str.size()-start));
			++tokens;
			break;
		} else {
			break;
		}
			start = str.find_first_not_of(sep,stop);
	}
	return vals;
}

bool ErosString::contains(std::string data) {
	if(stringData.find(data) != std::string::npos) {
		return true;
	}
	return false;
}

int ErosString::length() {
	return stringData.length();
}

std::string ErosString::toUpper() {
	std::transform(stringData.begin(), stringData.end(), stringData.begin(), ::toupper);
	return stringData;
}

std::string ErosString::toLower() {
	std::transform(stringData.begin(), stringData.end(), stringData.begin(), ::tolower);
	return stringData;
}