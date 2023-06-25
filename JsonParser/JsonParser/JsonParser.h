#pragma once
#include <fstream>
#include "MyString.h"
#include "JsonDataModel.h"
#include "JsonObject.h"
#include "JsonArray.h"

// A singleton class for parsing JSON data from and to a given stream
class JsonParser
{
	static const char STRING_SEPARATOR = '"';
	static const char OBJECT_START = '{';
	static const char OBJECT_END = '}';
	static const char ARRAY_START = '[';
	static const char ARRAY_END = ']';
	static const char COLON = ':';
	static const char COMMA = ',';
	static const char FALSE_PREFIX = 'f';
	static const char TRUE_PREFIX = 't';
	static const char NULL_PREFIX = 'n';
	static const char NEGATIVE_NUMBER = '-';

	mutable unsigned int linesCounter = 0;

	// Nested structure for easier parsing of data
	struct Token
	{
		enum class TokenType
		{
			OBJECT_START,
			OBJECT_END,
			ARRAY_START,
			ARRAY_END,
			COMMA,
			COLON,
			STRING,
			TRUE,
			FALSE,
			NUMBER,
			NULL_VALUE
		};

		MyString value;
		TokenType type;
	};

	// Singleton implementation
	JsonParser() = default;
	JsonParser(const JsonParser&) = delete;
	JsonParser& operator=(const JsonParser&) = delete;

	// Function for making errors more clear
	MyString getNewErrorText(const MyString& oldErrorText) const;

	// Function for getting next non-whitespace char
	char getNextChar(std::istream& inputStream) const;

	// Token creation functions
	Token createStringToken(std::istream& inputStream) const;
	Token createTrueToken(std::istream& inputStream) const;
	Token createFalseToken(std::istream& inputStream) const;
	Token createNullToken(std::istream& inputStream) const;
	Token createNumberToken(std::istream& inputStream, char startingSymbol) const;
	Token getNextToken(std::istream& inputStream) const;

	// Functions for parsing Json Nodes
	JsonNode* parseToken(const Token& current, std::istream& inputStream) const;
	JsonObject* parseObject(std::istream& inputStream) const;
	JsonArray* parseArray(std::istream& inputStream) const;
public:
	// Singleton instance getter
	static JsonParser& getInstance();

	// Parser functionallity interface
	JsonDataModel read(std::istream& inputStream) const;
	void write(std::ostream& outputStream, JsonNode* model) const;
};