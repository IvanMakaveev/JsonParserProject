#include "ReadFromFileCommand.h"

#include <fstream>
#include "JsonParser.h"

ReadFromFileCommand::ReadFromFileCommand(const MyString& path) : filePath(path)
{

}

void ReadFromFileCommand::execute(JsonDataModel& model)
{
	std::ifstream ifs(filePath.c_str());

	if (!ifs.is_open())
	{
		ifs.close();
		throw std::runtime_error("Could not load the given file!");
	}
	model = std::move(JsonParser::getInstance().read(ifs));
	ifs.close();
}
