#ifndef STRING_PARSER_H
#define STRING_PARSER_H

#include <vector>
#include <string>

class StringParser
{
public:
	StringParser();
	StringParser(const char delimiter);
	StringParser(const char delimiter, const bool trailing_delimiter);
	void parse(const std::string line, std::vector<std::string> &parsed_line) const;

private:
	char delimiter;
	bool trailing_delimiter;
};

#endif