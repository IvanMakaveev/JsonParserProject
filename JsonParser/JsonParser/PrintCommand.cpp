#include "PrintCommand.h"

void PrintCommand::execute(JsonDataModel& model)
{
	model.print();
	std::cout << std::endl;
}
