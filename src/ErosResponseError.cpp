#include "ErosResponseError.h"
#include "ErosConfig.h"
#include "ErosFile.h"

std::string ErosResponseError::get404() {
	std::string content;
	
	ErosFile nCustom404File(ErosConfig::workspace + "/404.html");
	if (nCustom404File.exist()) {
		content = nCustom404File.content();
	} else {
		ErosFile n404File("res/html/404.html");
		content = n404File.content();
	}

	ErosResponse response;
	response.setStatus(_404);
	response.setContent(content);
	return response.parse();
}
