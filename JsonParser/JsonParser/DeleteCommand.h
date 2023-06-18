#pragma once
#include "JsonCommand.h"

// Command for deleting a node at a given path
class DeleteCommand : public JsonCommand
{
	MyString path;
public:
	DeleteCommand(const MyString& path);

	void execute(JsonDataModel& model) override;
};
