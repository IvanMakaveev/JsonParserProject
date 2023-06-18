#pragma once
#include "JsonCommand.h"

class SaveToFileCommand : public JsonCommand
{
	MyString filePath;
	MyString modelPath;
public:
	SaveToFileCommand(const MyString& filePath, const MyString& modelPath);

	void execute(JsonDataModel& model) override;
};

