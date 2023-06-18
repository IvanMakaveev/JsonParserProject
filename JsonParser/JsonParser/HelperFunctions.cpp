#include "HelperFunctions.h"
#include <iostream>
#include <stdexcept>

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
