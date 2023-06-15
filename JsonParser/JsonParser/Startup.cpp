#include <iostream>
#include "JsonDataModel.h"
#include "JsonParser.h"
#include "JsonConsoleCommandFactory.h"

int main()
{
	std::ifstream ifs("read.json");

	JsonDataModel model = JsonParser().read(ifs);
	model.print();
	ifs.close();

	//ApplicationCommandExecutor app;

	while (false)
	{
		JsonConsoleCommandFactory::getInstance().getCommand();
		//app.executeCommand(...)
	}
}