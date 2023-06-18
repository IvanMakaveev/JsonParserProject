#pragma once
#include "JsonCommand.h"

// Command for searching in JSON Data Model
class SearchCommand :public JsonCommand
{
	MyString searchKey;
public:
	SearchCommand(const MyString& key);

	void execute(JsonDataModel& model) override;
};

