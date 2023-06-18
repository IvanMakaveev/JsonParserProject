#include "SaveToFileCommand.h"
#include "JsonParser.h"
#include <fstream>

SaveToFileCommand::SaveToFileCommand(const MyString& filePath, const MyString& modelPath) :filePath(filePath), modelPath(modelPath)
{

}

void SaveToFileCommand::execute(JsonDataModel& model)
{
	std::ofstream ofs(filePath.c_str());
	JsonParser().write(ofs, model.getElementAt(modelPath));
	ofs.close();
}
