#ifndef __EROSCAST_H__
#define __EROSCAST_H__

#include <iostream>
#include <sstream>
#include <string>

template <class T>
class ErosCast {
	public:
		static std::string toString(T t);
		static std::string toHex(T t);
		static std::string toDecimal(T t);
		static T toType(const std::string &s);
};


template<class T>
std::string ErosCast<T>::toString(T t) {
	std::stringstream stream;
	stream << t;
	return stream.str();
}


template<class T>
std::string ErosCast<T>::toHex(T t) {
	std::stringstream stream;
	stream << std::hex << t;
	return stream.str();
}


template<class T>
std::string ErosCast<T>::toDecimal(T t) {
	std::stringstream stream;
	stream << std::dec << t;
	return stream.str();
}


template<class T>
T ErosCast<T>::toType(const std::string &s) {
	std::stringstream stream(s);
	T t;
	stream >> t;
	return t;
}
#endif