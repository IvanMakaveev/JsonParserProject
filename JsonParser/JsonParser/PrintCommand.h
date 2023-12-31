#pragma once
#include "JsonCommand.h"

// Command for printing a JSON Data Model
class PrintCommand : public JsonCommand
{
public:
	void execute(JsonDataModel& model) override;
};

