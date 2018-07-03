#include "ErosConfig.h"

std::string ErosConfig::workspace;
unsigned short ErosConfig::port;

void ErosConfig::load(const std::string& file) {
	std::ifstream in;
	in.open(file.c_str(), std::ios::in);
	if (in.is_open()) {
		parse(in);
	}
	in.close();
}

void ErosConfig::parse(std::ifstream& in) {
	std::stringstream stream;	
	char c;
	while (in >> c) {
		if (c == '(' || c == '{' || c == '}') {
			continue;	
		} else if (c == ')') {
			stream >> port;
			stream.str("");
			stream.clear();
		} else if (c == '[') {
			continue;
		} else if (c == ']') {
			stream >> workspace;
			stream.str("");
			stream.clear();
		} else {
			stream << c;
		}
	}
}