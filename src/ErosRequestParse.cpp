#include "ErosRequestParse.h"
#include "ErosString.h"
#include "ErosCast.h"

#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
#include <vector>

bool ErosRequestParse::checkIfConnection(const ErosRequest::HeaderItem &item)
{
	return item.name.compare("Connection") == 0;
}

ErosRequestParse::ErosRequestParse()
		: state(RequestMethodStart), contentSize(0),
		  chunkSize(0), chunked(false)
{}

ParseResult ErosRequestParse::parse(ErosRequest &req, const std::string& message) {
	ParseResult result = parseHeader(req, message);
	if (result != ParsingCompleted) {
		return result;
	}

	return parseParams(req, req.getContent());
}

ParseResult ErosRequestParse::parseHeader(ErosRequest &req, const std::string& message) {
	const char *begin =  message.c_str();
	const char *end = message.c_str() + message.length();

	std::string method = "";
	std::string uri = "";
	std::vector<char> content;

	while( begin != end )
	{
		char input = *begin++;

		switch (state)
		{
			case RequestMethodStart:
				if( !isChar(input) || isControl(input) || isSpecial(input) )
				{
					return ParsingError;
				}
				else
				{
					state = RequestMethod;
					method.push_back(input);
				}
				break;
			case RequestMethod:
				if( input == ' ' )
				{
					state = RequestUriStart;
				}
				else if( !isChar(input) || isControl(input) || isSpecial(input) )
				{
					return ParsingError;
				}
				else
				{
					method.push_back(input);
				}
				break;
			case RequestUriStart:
				if( isControl(input) )
				{
					return ParsingError;
				}
				else
				{
					state = RequestUri;
					uri.push_back(input);
				}
				break;
			case RequestUri:
				if( input == ' ' )
				{
					state = RequestHttpVersion_h;
				}
				else if (input == '\r')
				{
					req.setVersionMajor(0);
					req.setVersionMinor(9);
					req.setContent(std::string(content.begin(), content.end()));

					return ParsingCompleted;
				}
				else if( isControl(input) )
				{
					return ParsingError;
				}
				else
				{
					uri.push_back(input);
				}
				break;
			case RequestHttpVersion_h:
				if( input == 'H' )
				{
					state = RequestHttpVersion_ht;
				}
				else
				{
					return ParsingError;
				}
				break;
			case RequestHttpVersion_ht:
				if( input == 'T' )
				{
					state = RequestHttpVersion_htt;
				}
				else
				{
					return ParsingError;
				}
				break;
			case RequestHttpVersion_htt:
				if( input == 'T' )
				{
					state = RequestHttpVersion_http;
				}
				else
				{
					return ParsingError;
				}
				break;
			case RequestHttpVersion_http:
				if( input == 'P' )
				{
					state = RequestHttpVersion_slash;
				}
				else
				{
					return ParsingError;
				}
				break;
			case RequestHttpVersion_slash:
				if( input == '/' )
				{
					req.setVersionMajor(0);
					req.setVersionMinor(0);
					state = RequestHttpVersion_majorStart;
				}
				else
				{
					return ParsingError;
				}
				break;
			case RequestHttpVersion_majorStart:
				if( isDigit(input) )
				{
					req.setVersionMajor(input - '0');
					state = RequestHttpVersion_major;
				}
				else
				{
					return ParsingError;
				}
				break;
			case RequestHttpVersion_major:
				if( input == '.' )
				{
					state = RequestHttpVersion_minorStart;
				}
				else if (isDigit(input))
				{
					req.setVersionMajor(req.getVersionMajor() * 10 + input - '0');
				}
				else
				{
					return ParsingError;
				}
				break;
			case RequestHttpVersion_minorStart:
				if( isDigit(input) )
				{
					req.setVersionMinor(input - '0');
					state = RequestHttpVersion_minor;
				}
				else
				{
					return ParsingError;
				}
				break;
			case RequestHttpVersion_minor:
				if( input == '\r' )
				{
					state = ResponseHttpVersion_newLine;
				}
				else if( isDigit(input) )
				{
					req.setVersionMinor(req.getVersionMinor() * 10 + input - '0');
				}
				else
				{
					return ParsingError;
				}
				break;
			case ResponseHttpVersion_newLine:
				if( input == '\n' )
				{
					state = HeaderLineStart;
				}
				else
				{
					return ParsingError;
				}
				break;
			case HeaderLineStart:
				if( input == '\r' )
				{
					state = ExpectingNewline_3;
				}
				else if( !req.getHeaders().empty() && (input == ' ' || input == '\t') )
				{
					state = HeaderLws;
				}
				else if( !isChar(input) || isControl(input) || isSpecial(input) )
				{
					return ParsingError;
				}
				else
				{
					req.getHeaders().push_back(ErosRequest::HeaderItem());
					req.getHeaders().back().name.reserve(16);
					req.getHeaders().back().value.reserve(16);
					req.getHeaders().back().name.push_back(input);
					state = HeaderName;
				}
				break;
			case HeaderLws:
				if( input == '\r' )
				{
					state = ExpectingNewline_2;
				}
				else if( input == ' ' || input == '\t' )
				{
				}
				else if( isControl(input) )
				{
					return ParsingError;
				}
				else
				{
					state = HeaderValue;
					req.getHeaders().back().value.push_back(input);
				}
				break;
			case HeaderName:
				if( input == ':' )
				{
					state = SpaceBeforeHeaderValue;
				}
				else if( !isChar(input) || isControl(input) || isSpecial(input) )
				{
					return ParsingError;
				}
				else
				{
					req.getHeaders().back().name.push_back(input);
				}
				break;
			case SpaceBeforeHeaderValue:
				if( input == ' ' )
				{
					state = HeaderValue;
				}
				else
				{
					return ParsingError;
				}
				break;
			case HeaderValue:
				if( input == '\r' )
				{
					if( method == "POST" || method == "PUT" )
					{
						ErosRequest::HeaderItem &h = req.getHeaders().back();

						if( h.name.compare("Content-Length") == 0 )
						{
							contentSize = atoi(h.value.c_str());
							content.reserve( contentSize );
						}
						else if(h.name.compare("Transfer-Encoding") == 0 )
						{
							if(h.value.compare("chunked") == 0)
								chunked = true;
						}
					}
					state = ExpectingNewline_2;
				}
				else if( isControl(input) )
				{
					return ParsingError;
				}
				else
				{
					req.getHeaders().back().value.push_back(input);
				}
				break;
			case ExpectingNewline_2:
				if( input == '\n' )
				{
					state = HeaderLineStart;
				}
				else
				{
					return ParsingError;
				}
				break;
			case ExpectingNewline_3: {
				std::vector<ErosRequest::HeaderItem>::iterator it = std::find_if(req.getHeaders().begin(),
																			 req.getHeaders().end(),
																			 checkIfConnection);

				if( it != req.getHeaders().end() )
				{
					if (it->value.compare("Keep-Alive") == 0)
					{
						req.setKeepAlive(true);
					}
					else  // == Close
					{
						req.setKeepAlive(false);
					}
				}
				else
				{
					if( req.getVersionMajor() > 1 || (req.getVersionMajor() == 1 && req.getVersionMinor() == 1) )
						req.setKeepAlive(true);
				}

				if( chunked )
				{
					state = ChunkSize;
				}
				else if( contentSize == 0 )
				{
					if( input == '\n') {
						req.setContent(std::string(content.begin(), content.end()));
						req.setPath(uri);
						req.setMethod(method);

						return ParsingCompleted;
					} else {
						return ParsingError;
					}
				}
				else
				{
					state = Post;
				}
				break;
			}
			case Post:
				--contentSize;
				content.push_back( input );

				if( contentSize == 0 )
				{
					req.setContent(std::string(content.begin(), content.end()));
					req.setPath(uri);
					req.setMethod(method);

					return ParsingCompleted;
				}
				break;
			case ChunkSize:
				if( isalnum(input) )
				{
					chunkSizeStr.push_back(input);
				}
				else if( input == ';' )
				{
					state = ChunkExtensionName;
				}
				else if( input == '\r' )
				{
					state = ChunkSizeNewLine;
				}
				else
				{
					return ParsingError;
				}
				break;
			case ChunkExtensionName:
				if( isalnum(input) || input == ' ' )
				{
					// skip
				}
				else if( input == '=' )
				{
					state = ChunkExtensionValue;
				}
				else if( input == '\r' )
				{
					state = ChunkSizeNewLine;
				}
				else
				{
					return ParsingError;
				}
				break;
			case ChunkExtensionValue:
				if( isalnum(input) || input == ' ' )
				{
					// skip
				}
				else if( input == '\r' )
				{
					state = ChunkSizeNewLine;
				}
				else
				{
					return ParsingError;
				}
				break;
			case ChunkSizeNewLine:
				if( input == '\n' )
				{
					chunkSize = strtol(chunkSizeStr.c_str(), NULL, 16);
					chunkSizeStr.clear();
					content.reserve(content.size() + chunkSize);

					if( chunkSize == 0 )
						state = ChunkSizeNewLine_2;
					else
						state = ChunkData;
				}
				else
				{
					return ParsingError;
				}
				break;
			case ChunkSizeNewLine_2:
				if( input == '\r' )
				{
					state = ChunkSizeNewLine_3;
				}
				else if( isalpha(input) )
				{
					state = ChunkTrailerName;
				}
				else
				{
					return ParsingError;
				}
				break;
			case ChunkSizeNewLine_3:
				if( input == '\n' )
				{
					req.setContent(std::string(content.begin(), content.end()));
					req.setPath(uri);
					req.setMethod(method);

					return ParsingCompleted;
				}
				else
				{
					return ParsingError;
				}
				break;
			case ChunkTrailerName:
				if( isalnum(input) )
				{
					// skip
				}
				else if( input == ':' )
				{
					state = ChunkTrailerValue;
				}
				else
				{
					return ParsingError;
				}
				break;
			case ChunkTrailerValue:
				if( isalnum(input) || input == ' ' )
				{
					// skip
				}
				else if( input == '\r' )
				{
					state = ChunkSizeNewLine;
				}
				else
				{
					return ParsingError;
				}
				break;
			case ChunkData:
				content.push_back(input);

				if( --chunkSize == 0 )
				{
					state = ChunkDataNewLine_1;
				}
				break;
			case ChunkDataNewLine_1:
				if( input == '\r' )
				{
					state = ChunkDataNewLine_2;
				}
				else
				{
					return ParsingError;
				}
				break;
			case ChunkDataNewLine_2:
				if( input == '\n' )
				{
					state = ChunkSize;
				}
				else
				{
					return ParsingError;
				}
				break;
			default:
				return ParsingError;
		}
	}

	return ParsingIncompleted;
}

// Check if a byte is an HTTP character.
bool ErosRequestParse::isChar(int c) {
	return c >= 0 && c <= 127;
}

// Check if a byte is an HTTP control character.
bool ErosRequestParse::isControl(int c) {
	return (c >= 0 && c <= 31) || (c == 127);
}

// Check if a byte is defined as an HTTP special character.
bool ErosRequestParse::isSpecial(int c) {
	switch (c)
	{
		case '(': case ')': case '<': case '>': case '@':
		case ',': case ';': case ':': case '\\': case '"':
		case '/': case '[': case ']': case '?': case '=':
		case '{': case '}': case ' ': case '\t':
			return true;
		default:
			return false;
	}
}

// Check if a byte is a digit.
bool ErosRequestParse::isDigit(int c) {
	return c >= '0' && c <= '9';
}

ParseResult ErosRequestParse::parseParams(ErosRequest &req, const std::string& raw) {
	ErosString nRaw(raw);
	if (nRaw.contains("&")) {
		std::vector<std::string> vars = nRaw.splitString("&");
		for (std::vector<std::string>::iterator it = vars.begin(); it != vars.end(); ++it) {
			std::string var = *it;
			nRaw.setData(var);
			if (nRaw.contains("=")) {
				std::vector<std::string> varParam = nRaw.splitString("=");
				if (varParam.size() >= 2) {
					params[varParam[0]] = varParam[1];
					std::cout << varParam[0] << " " << varParam[1] << std::endl;
				}
			}
		}
	}

	return ParsingCompleted;
}
