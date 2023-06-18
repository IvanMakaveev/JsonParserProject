#include "SetCommand.h"

#include <sstream>
#include "JsonParser.h"

SetCommand::SetCommand(const MyString& path, const MyString& jsonString) : path(path), jsonString(jsonString)
{

}

void SetCommand::execute(JsonDataModel& model)
{
	std::stringstream jsonStream(jsonString.c_str());
	JsonDataModel resultModel = JsonParser::getInstance().read(jsonStream);
	model.set(path, std::move(resultModel));
}
