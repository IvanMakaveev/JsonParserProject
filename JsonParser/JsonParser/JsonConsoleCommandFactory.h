#pragma once
#include <sstream>
#include "JsonCommand.h"
#include "JsonDataModel.h"

// Console command factory with singleton pattern
class JsonConsoleCommandFactory
{
	mutable MyString previousPath;

	// Singleton implementation
	JsonConsoleCommandFactory() = default;
	JsonConsoleCommandFactory(const JsonConsoleCommandFactory&) = delete;
	JsonConsoleCommandFactory& operator=(const JsonConsoleCommandFactory&) = delete;

	// Command manipulation functions
	MyString getCommandToken(std::stringstream& commandStream) const;
	MyString getPathToken(std::stringstream& commandStream) const;
	MyString getJsonDataToken(std::stringstream& commandStream) const;

public:
	// Command factory method
	JsonCommand* getCommand() const;

	// Singleton instance getter
	static JsonConsoleCommandFactory& getInstance();
};

