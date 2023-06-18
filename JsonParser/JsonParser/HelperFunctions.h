#pragma once
#include <iostream>
#include "MyString.h"

/*
	Helper functions for use in all other classes
*/

void swap(char& first, char& second);

void writeIndentation(std::ostream& os, unsigned int depth);

bool isDigit(char symbol);

unsigned int toNumber(char symbol);

char toSymbol(unsigned int digit);

MyString toString(unsigned int number);