#include "JsonParser.h"
#include "JsonString.h"
#include "JsonNumber.h"
#include "JsonBool.h"
#include "JsonNull.h"
#include "HelperFunctions.h"
#include <sstream>

/*
	Function to add the line counter to the error message
*/

MyString JsonParser::getNewErrorText(const MyString& oldErrorText) const
{
	MyString result(oldErrorText);
	result += " The given error has occured on line: ";
	result += toString(linesCounter);

	return result;
}

/*
	Retrieving next non-whitespace caracter
*/

char JsonParser::getNextChar(std::istream& inputStream) const
{
	static const size_t WHITESPACE_COUNT = 3;
	static const char WHITESPACE_CHARS[WHITESPACE_COUNT + 1] = "\n\t ";
	static const char NEW_LINE = '\n';
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
				if (current == NEW_LINE)
				{
					linesCounter++;
				}
			}
		}

		if (!isWhiteSpace)
		{
			return current;
		}

	} while (true);
}

/*
	Token creation and validation
*/

JsonParser::Token JsonParser::createStringToken(std::istream& inputStream) const
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

JsonParser::Token JsonParser::createTrueToken(std::istream& inputStream) const
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

JsonParser::Token JsonParser::createFalseToken(std::istream& inputStream) const
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

JsonParser::Token JsonParser::createNullToken(std::istream& inputStream) const
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

JsonParser::Token JsonParser::createNumberToken(std::istream& inputStream, char startingSymbol) const
{
	static const char DECIMAL_SEPARATOR = '.';

	Token result;
	result.type = Token::TokenType::NUMBER;
	result.value += startingSymbol;

	char current = '\0';
	inputStream.get(current);

	while (isDigit(current) || current == DECIMAL_SEPARATOR)
	{
		if (inputStream.eof())
		{
			return result;
		}

		result.value += current;

		inputStream.get(current);
	}

	inputStream.seekg(-1, std::ios::cur);

	return result;
}

/*
	Token retrieval function
*/

JsonParser::Token JsonParser::getNextToken(std::istream& inputStream) const
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

	throw std::runtime_error("Symbol not matching any expected literal! Perhaps there is a missing format token!");
}

/*
	Json Object parsing
*/

JsonObject* JsonParser::parseObject(std::istream& inputStream) const
{
	JsonObject* result = new JsonObject();

	try
	{
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

			result->addElement(key, value);

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
	}
	catch (const std::runtime_error& re)
	{
		delete result;
		throw;
	}

	return result;
}

/*
	Json Array parsing
*/

JsonArray* JsonParser::parseArray(std::istream& inputStream) const
{
	JsonArray* result = new JsonArray();

	try
	{
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
	}
	catch (const std::runtime_error& re)
	{
		delete result;
		throw;
	}

	return result;
}

/*
	Token parser
*/

JsonNode* JsonParser::parseToken(const JsonParser::Token& currentToken, std::istream& inputStream) const
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

/*
	Singleton instance getter
*/

JsonParser& JsonParser::getInstance()
{
	static JsonParser parser;
	return parser;
}

/*
	Read from stream function
*/

JsonDataModel JsonParser::read(std::istream& inputStream) const
{
	linesCounter = 1;

	try
	{
		Token firstToken = getNextToken(inputStream);
		JsonNode* root = parseToken(firstToken, inputStream);
		return JsonDataModel(root);
	}
	catch (const std::runtime_error& rte)
	{
		MyString newErrorText = getNewErrorText(rte.what());
		throw std::runtime_error(newErrorText.c_str());
	}
	catch (const std::logic_error& le)
	{
		MyString newErrorText = getNewErrorText(le.what());
		throw std::logic_error(newErrorText.c_str());
	}
	catch (const std::exception& e)
	{
		MyString newErrorText = getNewErrorText(e.what());
		throw std::exception(newErrorText.c_str());
	}
}

/*
	Write to stream function - used recursively
*/

void JsonParser::write(std::ostream& outputStream, JsonNode* nodeToWrite) const
{
	nodeToWrite->writeFormatted(outputStream);
}
