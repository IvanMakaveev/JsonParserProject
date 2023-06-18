#pragma once
#include <sstream>
#include "JsonCommand.h"
#include "JsonDataModel.h"

class JsonConsoleCommandFactory
{
	mutable MyString previousPath;

	JsonConsoleCommandFactory() = default;

	JsonConsoleCommandFactory(const JsonConsoleCommandFactory&) = delete;
	JsonConsoleCommandFactory& operator=(const JsonConsoleCommandFactory&) = delete;

	MyString getCommandToken(std::stringstream& commandStream) const;
	MyString getPathToken(std::stringstream& commandStream) const;
	MyString getJsonDataToken(std::stringstream& commandStream) const;
public:
	JsonCommand* getCommand() const;
	static JsonConsoleCommandFactory& getInstance();
};

