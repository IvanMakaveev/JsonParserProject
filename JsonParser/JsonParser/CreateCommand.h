#pragma once
#include "JsonCommand.h"

class CreateCommand : public JsonCommand
{
	MyString path;
	MyString jsonString;
public:
	CreateCommand(const MyString& path, const MyString& jsonString);

	void execute(JsonDataModel& model) override;
};


