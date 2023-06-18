#include <iostream>
#include "JsonDataModel.h"
#include "JsonParser.h"
#include "ApplicationCommandExecutor.h"
#include "JsonConsoleCommandFactory.h"

int main()
{
	std::ifstream ifs("read.json");

	JsonDataModel model = JsonParser().read(ifs);
	model.print();
	ifs.close();

	ApplicationCommandExecutor app;

	while (false)
	{
		try
		{
			app.runCommand(JsonConsoleCommandFactory::getInstance().getCommand());
		}
		catch (const std::exception& exc)
		{
			std::cout << "An error has occured!!!" << std::endl;
			std::cout << exc.what() << std::endl;
		}
	}
}