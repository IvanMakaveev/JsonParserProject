#include "JsonConsoleCommandFactory.h"

#include <iostream>
#include <sstream>

#include "PrintCommand.h"
#include "SearchCommand.h"
#include "DeleteCommand.h"
#include "SetCommand.h"
#include "CreateCommand.h"
#include "SaveToFileCommand.h"
#include "ReadFromFileCommand.h"
#include "ExitCommand.h"

/*
	Command string stream manipulation
*/

MyString JsonConsoleCommandFactory::getCommandToken(std::stringstream& commandStream) const
{
	static const char COMMAND_DELIM = ' ';
	static const size_t BUFFER_SIZE = 64;
	static char buffer[BUFFER_SIZE] = { 0 };

	commandStream.getline(buffer, BUFFER_SIZE, COMMAND_DELIM);
	return MyString(buffer);
}

MyString JsonConsoleCommandFactory::getPathToken(std::stringstream& commandStream) const
{
	static const char STRING_SEPARATOR = '"';
	static const size_t BUFFER_SIZE = 1024;
	static char buffer[BUFFER_SIZE] = { 0 };

	char separator = '\0';
	commandStream >> separator;

	if (!separator)
	{
		return MyString();
	}

	if (separator != STRING_SEPARATOR)
	{
		throw std::invalid_argument("Invalid command parameters! Please pass path strings with quotation marks ( \" )!");
	}

	commandStream.getline(buffer, BUFFER_SIZE, STRING_SEPARATOR);
	return MyString(buffer);
}

MyString JsonConsoleCommandFactory::getJsonDataToken(std::stringstream& commandStream) const
{
	static const char STRING_SEPARATOR = '"';
	static const size_t BUFFER_SIZE = 1024;
	static char buffer[BUFFER_SIZE] = { 0 };

	char separator = '\0';
	commandStream >> separator;

	if (separator != STRING_SEPARATOR)
	{
		throw std::invalid_argument("Invalid command parameters! Please pass json strings with leading quotation marks ( \" )!");
	}

	commandStream.getline(buffer, BUFFER_SIZE);
	MyString result(buffer);

	if (result[result.length() - 1] != STRING_SEPARATOR)
	{
		throw std::invalid_argument("Invalid command parameters! Please pass json strings with trailing quotation marks ( \" )!");
	}

	result[result.length() - 1] = '\0';
	return result;
}

/*
	Command factory method
*/

JsonCommand* JsonConsoleCommandFactory::getCommand() const
{
	static const size_t BUFFER_SIZE = 1024;
	static char buffer[BUFFER_SIZE] = { 0 };

	std::cin.getline(buffer, BUFFER_SIZE);
	std::stringstream commandStream(buffer);

	MyString command = getCommandToken(commandStream);

	if (command == "print")
	{
		return new PrintCommand();
	}

	if (command == "search")
	{
		MyString path = getPathToken(commandStream);
		return new SearchCommand(path);
	}

	if (command == "set")
	{
		MyString path = getPathToken(commandStream);
		MyString jsonData = getJsonDataToken(commandStream);
		return new SetCommand(path, jsonData);
	}

	if (command == "create")
	{
		MyString path = getPathToken(commandStream);
		MyString jsonData = getJsonDataToken(commandStream);
		return new CreateCommand(path, jsonData);
	}

	if (command == "delete")
	{
		MyString path = getPathToken(commandStream);
		return new DeleteCommand(path);
	}

	if (command == "load")
	{
		previousPath = getPathToken(commandStream);
		return new ReadFromFileCommand(previousPath);
	}

	if (command == "save")
	{
		MyString jsonPath = getPathToken(commandStream);
		return new SaveToFileCommand(previousPath, jsonPath);
	}

	if (command == "saveas")
	{
		MyString filePath = getPathToken(commandStream);
		MyString jsonPath  = getPathToken(commandStream);
		return new SaveToFileCommand(filePath, jsonPath);
	}

	if (command == "exit")
	{
		return new ExitCommand();
	}

	return nullptr;
}

/*
	Instance singleton getter
*/

JsonConsoleCommandFactory& JsonConsoleCommandFactory::getInstance()
{
	static JsonConsoleCommandFactory factory;
	return factory;
}
