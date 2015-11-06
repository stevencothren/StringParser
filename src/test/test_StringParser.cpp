#ifndef CATCH_INCLUDED
#define CATCH_INCLUDED
#include "catch.hpp"
#endif

#include "../StringParser.hpp"
#include <vector>

TEST_CASE("Single Value With No Delimiters")
{
	std::vector<std::string> parsed_line;

	SECTION("Default Constructor")
	{
		std::string line("One");
		StringParser parser('|');
		parser.parse(line, parsed_line);

		REQUIRE(parsed_line.size() == 1);
		REQUIRE(parsed_line[0].compare("One") == 0);
	}

	SECTION("Trailing Delimiter")
	{
		std::string line("One|");
		StringParser parser('|', true);
		parser.parse(line, parsed_line);

		REQUIRE(parsed_line.size() == 1);
		REQUIRE(parsed_line[0].compare("One") == 0);
	}
}

TEST_CASE("Three Delimited Values")
{
	std::vector<std::string> parsed_line;

	SECTION("Default Constructor")
	{
		std::string line("One|Two|Three");
		StringParser parser('|');
		parser.parse(line, parsed_line);

		REQUIRE(parsed_line.size() == 3);
		REQUIRE(parsed_line[0].compare("One") == 0);
		REQUIRE(parsed_line[1].compare("Two") == 0);
		REQUIRE(parsed_line[2].compare("Three") == 0);
	}

	SECTION("Trailing Delimiter")
	{
		std::string line("One|Two|Three|");
		StringParser parser('|', true);
		parser.parse(line, parsed_line);

		REQUIRE(parsed_line.size() == 3);
		REQUIRE(parsed_line[0].compare("One") == 0);
		REQUIRE(parsed_line[1].compare("Two") == 0);
		REQUIRE(parsed_line[2].compare("Three") == 0);
	}
}

TEST_CASE("Two Delimited Values with a Quoted Delimiter")
{
	std::vector<std::string> parsed_line;

	SECTION("Default Constructor")
	{
		std::string line("One|\"Two|Three\"");
		StringParser parser('|');
		parser.parse(line, parsed_line);

		REQUIRE(parsed_line.size() == 2);
		REQUIRE(parsed_line[0].compare("One") == 0);
		REQUIRE(parsed_line[1].compare("\"Two|Three\"") == 0);
	}

	SECTION("Trailing Delimiter")
	{
		std::string line("One|\"Two|Three\"|");
		StringParser parser('|', true);
		parser.parse(line, parsed_line);

		REQUIRE(parsed_line.size() == 2);
		REQUIRE(parsed_line[0].compare("One") == 0);
		REQUIRE(parsed_line[1].compare("\"Two|Three\"") == 0);
	}
}

TEST_CASE("Two Delimited Values with a Derefed Delimiter")
{
	std::vector<std::string> parsed_line;

	SECTION("Default Constructor")
	{
		std::string line("One|Two\\|Three");
		StringParser parser('|');
		parser.parse(line, parsed_line);

		REQUIRE(parsed_line.size() == 2);
		REQUIRE(parsed_line[0].compare("One") == 0);
		REQUIRE(parsed_line[1].compare("Two\\|Three") == 0);
	}

	SECTION("Trailing Delimiter")
	{
		std::string line("One|Two\\|Three|");
		StringParser parser('|', true);
		parser.parse(line, parsed_line);

		REQUIRE(parsed_line.size() == 2);
		REQUIRE(parsed_line[0].compare("One") == 0);
		REQUIRE(parsed_line[1].compare("Two\\|Three") == 0);
	}
}

TEST_CASE("Three Delimited Values with a Derefed Quote")
{
	std::vector<std::string> parsed_line;

	SECTION("Default Constructor")
	{
		std::string line("One|\\\"Two|Three");
		StringParser parser('|');
		parser.parse(line, parsed_line);

		REQUIRE(parsed_line.size() == 3);
		REQUIRE(parsed_line[0].compare("One") == 0);
		REQUIRE(parsed_line[1].compare("\\\"Two") == 0);
		REQUIRE(parsed_line[2].compare("Three") == 0);
	}

	SECTION("Trailing Delimiter")
	{
		std::string line("One|\\\"Two|Three|");
		StringParser parser('|', true);
		parser.parse(line, parsed_line);

		REQUIRE(parsed_line.size() == 3);
		REQUIRE(parsed_line[0].compare("One") == 0);
		REQUIRE(parsed_line[1].compare("\\\"Two") == 0);
		REQUIRE(parsed_line[2].compare("Three") == 0);
	}
}

TEST_CASE("Three Delimited Values with a Hanging Quote")
{
	std::vector<std::string> parsed_line;

	SECTION("Default Constructor")
	{
		std::string line("One|Two|\"Three");
		StringParser parser('|');
		parser.parse(line, parsed_line);

		REQUIRE(parsed_line.size() == 3);
		REQUIRE(parsed_line[0].compare("One") == 0);
		REQUIRE(parsed_line[1].compare("Two") == 0);
		REQUIRE(parsed_line[2].compare("\"Three") == 0);
	}

	SECTION("Trailing Delimiter")
	{
		std::string line("One|Two|\"Three|");
		StringParser parser('|', true);
		parser.parse(line, parsed_line);

		REQUIRE(parsed_line.size() == 2);
		REQUIRE(parsed_line[0].compare("One") == 0);
		REQUIRE(parsed_line[1].compare("Two") == 0);
	}
}

TEST_CASE("Two Delimited Values due to a Hanging Quote")
{
	std::vector<std::string> parsed_line;

	SECTION("Default Constructor")
	{
		std::string line("One|\"Two|Three");
		StringParser parser('|');
		parser.parse(line, parsed_line);

		REQUIRE(parsed_line.size() == 2);
		REQUIRE(parsed_line[0].compare("One") == 0);
		REQUIRE(parsed_line[1].compare("\"Two|Three") == 0);
	}

	SECTION("Trailing Delimiter")
	{
		std::string line("One|\"Two|Three|");
		StringParser parser('|', true);
		parser.parse(line, parsed_line);

		REQUIRE(parsed_line.size() == 1);
		REQUIRE(parsed_line[0].compare("One") == 0);
	}
}