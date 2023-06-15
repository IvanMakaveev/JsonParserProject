#pragma once
#include "JsonCommand.h"
#include "JsonDataModel.h"

class JsonConsoleCommandFactory
{
	JsonDataModel model;

	JsonConsoleCommandFactory() = default;

	JsonConsoleCommandFactory(const JsonConsoleCommandFactory&) = delete;
	JsonConsoleCommandFactory& operator=(const JsonConsoleCommandFactory&) = delete;

public:
	JsonCommand* getCommand() const;
	static JsonConsoleCommandFactory& getInstance();
};

