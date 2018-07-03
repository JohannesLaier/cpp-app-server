#ifndef __FILE_H__
#define __FILE_H__

#include <string>

class ErosFile {
	private:
		std::string fileName;
	public:
		ErosFile(const std::string& fileName);
		bool exist();
		
		std::string content();
		std::string extension();
};
#endif
