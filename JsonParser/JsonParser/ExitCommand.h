#pragma once
#include "JsonCommand.h"

// Command for exiting the application
class ExitCommand : public JsonCommand
{
public:
	void execute(JsonDataModel& model) override;
};

