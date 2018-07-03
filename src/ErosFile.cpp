#include "ErosFile.h"

#include <fstream>
#include <sstream>

ErosFile::ErosFile(const std::string& fn) {
	fileName = fn;
}

bool ErosFile::exist() {
	std::ifstream in(fileName.c_str());
	bool exist = in.is_open();
	in.close();
	return exist;
}

std::string ErosFile::content() {
	std::string content;
	std::ifstream in(fileName.c_str());
	if (in.is_open()) {
		std::stringstream stream;
		stream << in.rdbuf();
		content = stream.str();
	}
	in.close();
	return content;
}

std::string ErosFile::extension() {
	std::size_t pos = fileName.find_last_of('.');
	if (pos != std::string::npos) {
		return fileName.substr(pos + 1);
	}
	return std::string();
}