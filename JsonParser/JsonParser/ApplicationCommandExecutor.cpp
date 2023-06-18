#include "ApplicationCommandExecutor.h"
#include "ReadFromFileCommand.h"

void ApplicationCommandExecutor::printHelp() const
{
	std::cout << "load \"file path\"" << std::endl;
	std::cout << "print" << std::endl;
	std::cout << "search \"keyword\"" << std::endl;
	std::cout << "set \"model path\" \"jsonString\"" << std::endl;
	std::cout << "create \"model path\" \"jsonString\"" << std::endl;
	std::cout << "delete \"model path\"" << std::endl;
	std::cout << "save [\"model path\"]" << std::endl;
	std::cout << "saveas \"new file path\" [\"model path\"]" << std::endl;
	std::cout << "===================================" << std::endl;
}

ApplicationCommandExecutor::ApplicationCommandExecutor()
{
	std::cout << "Hello user!" << std::endl;
	std::cout << "This is a JSON Parsing system. You can start by loading a JSON file." << std::endl;
	std::cout << "Here is a lost of all the commands:" << std::endl;
	printHelp();
}

void ApplicationCommandExecutor::runCommand(JsonCommand* command)
{
	if (command == nullptr)
	{
		std::cout << "It appears you have given an incorrect command!" << std::endl;
		std::cout << "Please use one of the following commands:" << std::endl;
		printHelp();
		return;
	}

	if (!model.hasInstance() && dynamic_cast<ReadFromFileCommand*>(command) == nullptr)
	{
		std::cout << "Before using any other commands, please load a JSON file!" << std::endl;
		delete command;
		return;
	}

	command->execute(model);

	delete command;
}
