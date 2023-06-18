#include "ReadFromFileCommand.h"
#include "JsonParser.h"
#include <fstream>

ReadFromFileCommand::ReadFromFileCommand(const MyString& path) : filePath(path)
{

}

void ReadFromFileCommand::execute(JsonDataModel& model)
{
	std::ifstream ifs(filePath.c_str());
	model = std::move(JsonParser().read(ifs));
	ifs.close();
}
