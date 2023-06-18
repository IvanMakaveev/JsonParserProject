#pragma once
#include "JsonCommand.h"

// Command for creating a node at a given path
class CreateCommand : public JsonCommand
{
	MyString path;
	MyString jsonString;
public:
	CreateCommand(const MyString& path, const MyString& jsonString);

	void execute(JsonDataModel& model) override;
};


