#pragma once
#include <fstream>
#include "MyString.h"
#include "JsonDataModel.h"
#include "JsonObject.h"
#include "JsonArray.h"

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

	char getNextChar(std::istream& inputStream);

	Token createStringToken(std::istream& inputStream);
	Token createTrueToken(std::istream& inputStream);
	Token createFalseToken(std::istream& inputStream);
	Token createNullToken(std::istream& inputStream);
	Token createNumberToken(std::istream& inputStream, char startingSymbol);
	Token getNextToken(std::istream& inputStream);

	JsonNode* parseToken(const Token& current, std::istream& inputStream);
	JsonObject* parseObject(std::istream& inputStream);
	JsonArray* parseArray(std::istream& inputStream);
public:
	JsonDataModel read(std::istream& inputStream);

	void write(const MyString& path)
	{

	}

	void validate()
	{

	}
};