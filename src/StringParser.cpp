#include "StringParser.hpp"

StringParser::StringParser()
{
	this->delimiter = '|';
	this->trailing_delimiter = false;
}

StringParser::StringParser(const char delimiter)
{
	this->delimiter = delimiter;
	this->trailing_delimiter = false;
}

StringParser::StringParser(const char delimiter, const bool trailing_delimiter)
{
	this->delimiter = delimiter;
	this->trailing_delimiter = trailing_delimiter;
}

void StringParser::parse(const std::string line, std::vector<std::string> &parsed_line) const
{
	int start_pos = 0;
	bool in_quote = false;
	bool derefed = false;

	for(int i = 0; i < line.length(); ++i)
	{
		if (derefed)
		{
			derefed = false;
		}
		else
		{
			if (line[i] == this->delimiter && !in_quote)
			{
				parsed_line.push_back(line.substr(start_pos, (i - start_pos)));
				start_pos = i+1;
			}
			else if (line[i] == '"')
			{
				in_quote = !in_quote;
			}
			else if (line[i] == '\\')
			{
				derefed = true;
			}
		}
	}

	if (!this->trailing_delimiter)
	{
		parsed_line.push_back(line.substr(start_pos, (line.length() - start_pos)));
	}
}