#include "JsonParser.h"
#include "JsonString.h"
#include "JsonNumber.h"
#include "JsonBool.h"
#include "JsonNull.h"
#include "HelperFunctions.h"
#include <sstream>

static double convertToNumber(const MyString& text)
{
	static const char NEGATIVE_SIGN = '-';
	static const char DECIMAL_SIGN = '.';
	double result = 0;
	bool isNegative = false;

	if (text[0] == NEGATIVE_SIGN)
	{
		isNegative = true;
	}
	else
	{
		result += toNumber(text[0]);
	}

	size_t textLen = text.length();
	bool isReadingDecimal = false;
	double decimalDivisor = 1;
	for (size_t i = 1; i < textLen; i++)
	{
		if (!isReadingDecimal)
		{
			if (text[i] == DECIMAL_SIGN)
			{
				isReadingDecimal = true;
				continue;
			}

			result *= 10;
			result += toNumber(text[i]);
		}
		else
		{
			decimalDivisor *= 10;
			result += (toNumber(text[i]) / decimalDivisor);
		}
	}

	return isNegative ? -result : result;
}

char JsonParser::getNextChar(std::istream& inputStream)
{
	static const size_t WHITESPACE_COUNT = 3;
	static const char WHITESPACE_CHARS[WHITESPACE_COUNT + 1] = "\n\t ";

	do
	{
		char current = '\0';
		inputStream.get(current);

		if (inputStream.eof())
		{
			throw std::logic_error("Could not find next character!");
		}

		bool isWhiteSpace = false;
		for (size_t i = 0; i < WHITESPACE_COUNT; i++)
		{
			if (WHITESPACE_CHARS[i] == current)
			{
				isWhiteSpace = true;
			}
		}

		if (!isWhiteSpace)
		{
			return current;
		}

	} while (true);
}

JsonParser::Token JsonParser::createStringToken(std::istream& inputStream)
{
	Token result;
	result.type = Token::TokenType::STRING;
	char current = '\0';
	inputStream.get(current);

	while (current != STRING_SEPARATOR)
	{
		if (inputStream.eof())
		{
			throw std::logic_error("Could not find end of string!");
		}
		result.value += current;
		inputStream.get(current);
	}

	return result;
}

JsonParser::Token JsonParser::createTrueToken(std::istream& inputStream)
{
	static const size_t WORD_LEN = 3;
	static const char REMAINING_WORD[WORD_LEN + 1] = "rue";
	Token result;
	result.type = Token::TokenType::TRUE;

	for (size_t i = 0; i < WORD_LEN; i++)
	{
		char current = '\0';

		inputStream.get(current);
		if (inputStream.eof())
		{
			throw std::logic_error("Could not find end of true value!");
		}

		if (current != REMAINING_WORD[i])
		{
			throw std::runtime_error("Unknown keyword reached! Attempted to read word true");
		}
	}

	return result;
}

JsonParser::Token JsonParser::createFalseToken(std::istream& inputStream)
{
	static const size_t WORD_LEN = 4;
	static const char REMAINING_WORD[WORD_LEN + 1] = "alse";
	Token result;
	result.type = Token::TokenType::FALSE;

	for (size_t i = 0; i < WORD_LEN; i++)
	{
		char current = '\0';

		inputStream.get(current);
		if (inputStream.eof())
		{
			throw std::logic_error("Could not find end of false value!");
		}

		if (current != REMAINING_WORD[i])
		{
			throw std::runtime_error("Unknown keyword reached! Attempted to read word false");
		}
	}

	return result;
}

JsonParser::Token JsonParser::createNullToken(std::istream& inputStream)
{
	static const size_t WORD_LEN = 3;
	static const char REMAINING_WORD[WORD_LEN + 1] = "ull";
	Token result;
	result.type = Token::TokenType::NULL_VALUE;

	for (size_t i = 0; i < WORD_LEN; i++)
	{
		char current = '\0';

		inputStream.get(current);
		if (inputStream.eof())
		{
			throw std::logic_error("Could not find end of null value!");
		}

		if (current != REMAINING_WORD[i])
		{
			throw std::runtime_error("Unknown keyword reached! Attempted to read word null");
		}
	}
	return result;
}

JsonParser::Token JsonParser::createNumberToken(std::istream& inputStream, char startingSymbol)
{
	static const char DECIMAL_SEPARATOR = '.';

	Token result;
	result.type = Token::TokenType::NUMBER;
	result.value += startingSymbol;

	char current = '\0';
	inputStream.get(current);

	while (isDigit(current) || current == DECIMAL_SEPARATOR)
	{
		result.value += current;

		if (inputStream.eof())
		{
			return result;
		}

		inputStream.get(current);
	}

	inputStream.seekg(-1, std::ios::cur);

	return result;
}

JsonParser::Token JsonParser::getNextToken(std::istream& inputStream)
{
	char current = getNextChar(inputStream);

	if (current == STRING_SEPARATOR)
	{
		return createStringToken(inputStream);
	}
	else if (current == FALSE_PREFIX)
	{
		return createFalseToken(inputStream);
	}
	else if (current == TRUE_PREFIX)
	{
		return createTrueToken(inputStream);
	}
	else if (current == NULL_PREFIX)
	{
		return createNullToken(inputStream);
	}
	else if (current == NULL_PREFIX)
	{
		return createNullToken(inputStream);
	}
	else if (current == OBJECT_START)
	{
		return Token{ "", Token::TokenType::OBJECT_START };
	}
	else if (current == OBJECT_END)
	{
		return Token{ "", Token::TokenType::OBJECT_END };
	}
	else if (current == ARRAY_START)
	{
		return Token{ "", Token::TokenType::ARRAY_START };
	}
	else if (current == ARRAY_END)
	{
		return Token{ "", Token::TokenType::ARRAY_END };
	}
	else if (current == COMMA)
	{
		return Token{ "", Token::TokenType::COMMA };
	}
	else if (current == COLON)
	{
		return Token{ "", Token::TokenType::COLON };
	}
	else if (isDigit(current) || current == NEGATIVE_NUMBER)
	{
		return createNumberToken(inputStream, current);
	}

	throw std::runtime_error("Symbol not matching any expected literal!");
}

JsonObject* JsonParser::parseObject(std::istream& inputStream)
{
	JsonObject* result = new JsonObject();

	Token currentToken = getNextToken(inputStream);

	while (currentToken.type != Token::TokenType::OBJECT_END)
	{
		if (currentToken.type != Token::TokenType::STRING)
		{
			throw std::runtime_error("Member key is missing!");
		}

		MyString key = std::move(currentToken.value);

		currentToken = getNextToken(inputStream);
		if (currentToken.type != Token::TokenType::COLON)
		{
			throw std::runtime_error("No colon between key and value of object member!");
		}

		currentToken = getNextToken(inputStream);
		JsonNode* value = parseToken(currentToken, inputStream);
		
		result->addMember(key, value);

		currentToken = getNextToken(inputStream);
		if (currentToken.type == Token::TokenType::COMMA)
		{
			currentToken = getNextToken(inputStream);
			if (currentToken.type == Token::TokenType::OBJECT_END)
			{
				throw std::runtime_error("Incorrect formatting of Json Object! Comman followed by end of object!");
			}
		}
		else if (currentToken.type != Token::TokenType::OBJECT_END)
		{
			throw std::runtime_error("Incorrect formatting of Json Object! No comma between two members!");
		}
	}

	return result;
}

JsonArray* JsonParser::parseArray(std::istream& inputStream)
{
	JsonArray* result = new JsonArray();

	Token currentToken = getNextToken(inputStream);

	while (currentToken.type != Token::TokenType::ARRAY_END)
	{
		result->addElement(parseToken(currentToken, inputStream));

		currentToken = getNextToken(inputStream);
		if (currentToken.type == Token::TokenType::COMMA)
		{
			currentToken = getNextToken(inputStream);
			if (currentToken.type == Token::TokenType::ARRAY_END)
			{
				throw std::runtime_error("Incorrect formatting of Json Array! Comman followed by end of array!");
			}
		}
		else if (currentToken.type != Token::TokenType::ARRAY_END)
		{
			throw std::runtime_error("Incorrect formatting of Json Array! No comma between two elements!");
		}
	}

	return result;
}

JsonNode* JsonParser::parseToken(const JsonParser::Token& currentToken, std::istream& inputStream)
{
	switch (currentToken.type)
	{
	case Token::TokenType::STRING:
		return new JsonString(currentToken.value);
	case Token::TokenType::NUMBER:
		return new JsonNumber(convertToNumber(currentToken.value));
	case Token::TokenType::TRUE:
		return new JsonBool(true);
	case Token::TokenType::FALSE:
		return new JsonBool(false);
	case Token::TokenType::NULL_VALUE:
		return new JsonNull();
	case Token::TokenType::OBJECT_START:
		return parseObject(inputStream);
	case Token::TokenType::ARRAY_START:
		return parseArray(inputStream);
	default:
		throw std::runtime_error("Unexpected sequence of tokens!");
	}
}

JsonDataModel JsonParser::read(std::istream& inputStream)
{
	Token firstToken = getNextToken(inputStream);

	JsonNode* root = parseToken(firstToken, inputStream);

	return JsonDataModel(root);
}

void JsonParser::write(std::ostream& outputStream, JsonDataModel model)
{
	model.write(outputStream);
}
