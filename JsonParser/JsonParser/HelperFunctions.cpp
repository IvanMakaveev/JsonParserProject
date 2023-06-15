#include "HelperFunctions.h"
#include <iostream>

void printIndentation(unsigned int depth)
{
	static const char INDENTATION_SYMBOL = '\t';

	for (size_t i = 0; i < depth; i++)
	{
		std::cout << INDENTATION_SYMBOL;
	}
}

bool isDigit(char symbol)
{
	return symbol >= '0' && symbol <= '9';
}
