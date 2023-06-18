#pragma once
#include "JsonDataModel.h"

// Abstract command class for command pattern
class JsonCommand
{
public:
	virtual ~JsonCommand() = default;

	// Abstract function for command execution of JSON Data Model
	virtual void execute(JsonDataModel& model) = 0;
};

