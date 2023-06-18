#pragma once
#include "JsonCommand.h"

class PrintCommand : public JsonCommand
{
public:
	void execute(JsonDataModel& model) override;
};

