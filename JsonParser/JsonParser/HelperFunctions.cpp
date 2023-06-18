#include "HelperFunctions.h"
#include <iostream>
#include <stdexcept>

void swap(char& first, char& second)
{
	unsigned int temp = first;
	first = second;
	second = temp;
}

void writeIndentation(std::ostream& os, unsigned int depth)
{
	static const char INDENTATION_SYMBOL = '\t';

	for (size_t i = 0; i < depth; i++)
	{
		os << INDENTATION_SYMBOL;
	}
}

bool isDigit(char symbol)
{
	return symbol >= '0' && symbol <= '9';
}

unsigned int toNumber(char symbol)
{
	if (isDigit(symbol))
	{
		return symbol - '0';
	}

	throw std::runtime_error("A symbol that is not a number has been passed!");
}

char toSymbol(unsigned int digit)
{
	if (digit < 10)
	{
		return digit + '0';
	}

	throw std::runtime_error("To symbol function recieved a number and not a digit!");
}

MyString toString(unsigned int number)
{
	MyString resultReversed;

	do
	{
		resultReversed += toSymbol(number % 10);
		number /= 10;
	} while (number != 0);

	size_t length = resultReversed.length();
	for (size_t i = 0; i < length / 2; i++)
	{
		swap(resultReversed[i], resultReversed[length - i - 1]);
	}

	return resultReversed;
}
