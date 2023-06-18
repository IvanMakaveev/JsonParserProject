#include "CreateCommand.h"

#include <sstream>
#include "JsonParser.h"

CreateCommand::CreateCommand(const MyString& path, const MyString& jsonString) : path(path), jsonString(jsonString)
{

}

void CreateCommand::execute(JsonDataModel& model)
{
	std::stringstream jsonStream(jsonString.c_str());
	JsonDataModel resultModel = JsonParser::getInstance().read(jsonStream);
	model.create(path, std::move(resultModel));
}
