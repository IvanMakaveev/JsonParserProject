#include "DeleteCommand.h"

DeleteCommand::DeleteCommand(const MyString& path) : path(path)
{

}

void DeleteCommand::execute(JsonDataModel& model)
{
	model.deleteAt(path);
}
