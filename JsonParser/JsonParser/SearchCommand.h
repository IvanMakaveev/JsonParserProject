#pragma once
#include "JsonCommand.h"

class SearchCommand :public JsonCommand
{
	MyString searchKey;
public:
	SearchCommand(const MyString& key);

	void execute(JsonDataModel& model) override;
};

