#include "SaveToFileCommand.h"

#include <fstream>
#include "JsonParser.h"

SaveToFileCommand::SaveToFileCommand(const MyString& filePath, const MyString& modelPath) :filePath(filePath), modelPath(modelPath)
{

}

void SaveToFileCommand::execute(JsonDataModel& model)
{
	std::ofstream ofs(filePath.c_str());

	if (!ofs.is_open())
	{
		ofs.close();
		throw std::runtime_error("Could not save the given file!");
	}

	JsonParser::getInstance().write(ofs, model.getElementAt(modelPath));
	ofs.close();
}
