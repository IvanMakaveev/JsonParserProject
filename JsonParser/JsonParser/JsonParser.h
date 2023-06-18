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
	char getNextChar(std::istream& inputStream);

	// Token creation functions
	Token createStringToken(std::istream& inputStream);
	Token createTrueToken(std::istream& inputStream);
	Token createFalseToken(std::istream& inputStream);
	Token createNullToken(std::istream& inputStream);
	Token createNumberToken(std::istream& inputStream, char startingSymbol);
	Token getNextToken(std::istream& inputStream);

	// Functions for parsing Json Nodes
	JsonNode* parseToken(const Token& current, std::istream& inputStream);
	JsonObject* parseObject(std::istream& inputStream);
	JsonArray* parseArray(std::istream& inputStream);
public:
	// Singleton instance getter
	static JsonParser& getInstance();

	// Parser functionallity interface
	JsonDataModel read(std::istream& inputStream);
	void write(std::ostream& outputStream, JsonNode* model);
};