#pragma once
#include "JsonCommand.h"

class SetCommand : public JsonCommand
{
	MyString path;
	MyString jsonString;
public:
	SetCommand(const MyString& path, const MyString& jsonString);

	void execute(JsonDataModel& model) override;
};

