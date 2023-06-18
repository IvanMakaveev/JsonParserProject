#include <iostream>
#include "JsonDataModel.h"
#include "JsonParser.h"
#include "ApplicationCommandExecutor.h"
#include "JsonConsoleCommandFactory.h"

int main()
{
	ApplicationCommandExecutor app;

	while (true)
	{
		try
		{
			bool exit = app.runCommand(JsonConsoleCommandFactory::getInstance().getCommand());
			if (exit)
			{
				return 0;
			}
		}
		catch (const std::exception& exc)
		{
			app.printLineSeparator();
			std::cout << "An error has occured!!!" << std::endl;
			std::cout << exc.what() << std::endl;
			app.printLineSeparator();
		}
	}
}