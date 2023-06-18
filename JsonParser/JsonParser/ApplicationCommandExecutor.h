#pragma once
#include "JsonDataModel.h"
#include "JsonCommand.h"

class ApplicationCommandExecutor
{
	JsonDataModel model;

public:
	ApplicationCommandExecutor();
	void printHelp() const;
	void printLineSeparator() const;
	bool runCommand(JsonCommand* command);
};

