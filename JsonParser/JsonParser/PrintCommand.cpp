#include "PrintCommand.h"

void PrintCommand::execute(JsonDataModel& model)
{
	model.print();
}
