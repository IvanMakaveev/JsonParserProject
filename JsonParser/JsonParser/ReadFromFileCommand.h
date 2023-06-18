#pragma once
#include "JsonCommand.h"

class ReadFromFileCommand : public JsonCommand 
{
	MyString filePath;
public:
	ReadFromFileCommand(const MyString& path);

	void execute(JsonDataModel& model) override;
};

