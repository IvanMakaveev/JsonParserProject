#pragma once
#include "JsonDataModel.h"
#include "JsonCommand.h"

// Class for running the working console environment
class ApplicationCommandExecutor
{
	JsonDataModel model;

public:
	ApplicationCommandExecutor();
	void printHelp() const;
	void printLineSeparator() const;
	bool runCommand(JsonCommand* command);
};

