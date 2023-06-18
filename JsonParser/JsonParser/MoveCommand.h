#pragma once
#include "JsonCommand.h"

// Command for moving a node's data to a different node
class MoveCommand : public JsonCommand
{
	MyString fromPath;
	MyString toPath;
public:
	MoveCommand(const MyString& fromPath, const MyString& toPath);

	void execute(JsonDataModel& model) override;
};

