#pragma once
#include "JsonCommand.h"

// Command for reading JSON Data from file
class ReadFromFileCommand : public JsonCommand 
{
	MyString filePath;
public:
	ReadFromFileCommand(const MyString& path);

	void execute(JsonDataModel& model) override;
};

