#pragma once
#include "JsonDataModel.h"
#include "JsonCommand.h"

class ApplicationCommandExecutor
{
	JsonDataModel model;
	void printHelp() const;

public:
	ApplicationCommandExecutor();
	void runCommand(JsonCommand* command);
};

