#pragma once
#include "JsonCommand.h"

class DeleteCommand : public JsonCommand
{
	MyString path;
public:
	DeleteCommand(const MyString& path);

	void execute(JsonDataModel& model) override;
};
