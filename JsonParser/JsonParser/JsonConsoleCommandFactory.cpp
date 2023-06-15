#include "JsonConsoleCommandFactory.h"

JsonCommand* JsonConsoleCommandFactory::getCommand() const
{
	return nullptr;
}

JsonConsoleCommandFactory& JsonConsoleCommandFactory::getInstance()
{
	static JsonConsoleCommandFactory factory;
	return factory;
}
