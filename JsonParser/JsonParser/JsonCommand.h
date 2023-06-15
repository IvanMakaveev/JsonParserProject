#pragma once
#include "JsonDataModel.h"

class JsonCommand
{
public:
	virtual ~JsonCommand() = default;
	virtual void execute(JsonDataModel& model) = 0;
};

