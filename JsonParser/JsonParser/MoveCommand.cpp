#include "MoveCommand.h"

MoveCommand::MoveCommand(const MyString& fromPath, const MyString& toPath) : fromPath(fromPath), toPath(toPath)
{

}

void MoveCommand::execute(JsonDataModel& model)
{
	model.move(fromPath, toPath);
}
