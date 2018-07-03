#ifndef __REQUESTPARSE_H__
#define __REQUESTPARSE_H__

#include <string>
#include <map>

#include "../res/ErosRequest.h"

enum REQUESTTYPE {
	GET = 0, POST
};

enum ParseResult {
	ParsingCompleted,
	ParsingIncompleted,
	ParsingError
};


// The current state of the parser.
enum State
{
	RequestMethodStart,
	RequestMethod,
	RequestUriStart,
	RequestUri,
	RequestHttpVersion_h,
	RequestHttpVersion_ht,
	RequestHttpVersion_htt,
	RequestHttpVersion_http,
	RequestHttpVersion_slash,
	RequestHttpVersion_majorStart,
	RequestHttpVersion_major,
	RequestHttpVersion_minorStart,
	RequestHttpVersion_minor,

	ResponseStatusStart,
	ResponseHttpVersion_ht,
	ResponseHttpVersion_htt,
	ResponseHttpVersion_http,
	ResponseHttpVersion_slash,
	ResponseHttpVersion_majorStart,
	ResponseHttpVersion_major,
	ResponseHttpVersion_minorStart,
	ResponseHttpVersion_minor,
	ResponseHttpVersion_spaceAfterVersion,
	ResponseHttpVersion_statusCodeStart,
	ResponseHttpVersion_spaceAfterStatusCode,
	ResponseHttpVersion_statusTextStart,
	ResponseHttpVersion_newLine,

	HeaderLineStart,
	HeaderLws,
	HeaderName,
	SpaceBeforeHeaderValue,
	HeaderValue,
	ExpectingNewline_2,
	ExpectingNewline_3,

	Post,
	ChunkSize,
	ChunkExtensionName,
	ChunkExtensionValue,
	ChunkSizeNewLine,
	ChunkSizeNewLine_2,
	ChunkSizeNewLine_3,
	ChunkTrailerName,
	ChunkTrailerValue,

	ChunkDataNewLine_1,
	ChunkDataNewLine_2,
	ChunkData,
};

class ErosRequestParse {
	private:
		std::string path;
		REQUESTTYPE type;
		std::map<std::string, std::string> params;

		State state;

		size_t contentSize;
		std::string chunkSizeStr;
		size_t chunkSize;
		bool chunked;

		bool isChar(int c);
		bool isControl(int c);
		bool isSpecial(int c);
		bool isDigit(int c);

		static bool checkIfConnection(const ErosRequest::HeaderItem& item);

	public:
		ErosRequestParse();

		ParseResult parse(ErosRequest &req, const std::string& message);
		ParseResult parseHeader(ErosRequest &req, const std::string& message);
		ParseResult parseParams(ErosRequest &req, const std::string& params);
};
#endif
