#pragma once
#include "JsonCommand.h"

// Command for writing JSON Data to file
class SaveToFileCommand : public JsonCommand
{
	MyString filePath;
	MyString modelPath;
public:
	SaveToFileCommand(const MyString& filePath, const MyString& modelPath);

	void execute(JsonDataModel& model) override;
};

