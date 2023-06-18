#include "JsonDataModel.h"

void JsonDataModel::free()
{
	delete value;
	value = nullptr;
}

void JsonDataModel::copyFrom(const JsonDataModel& other)
{
	if (other.hasInstance())
	{
		value = other.value->clone();
	}
}

void JsonDataModel::moveFrom(JsonDataModel&& other)
{
	value = other.value;

	other.value = nullptr;
}

JsonDataModel::JsonDataModel() : value(nullptr)
{

}

JsonDataModel::JsonDataModel(JsonNode* value) : value(value)
{

}

JsonDataModel::JsonDataModel(const JsonDataModel& other)
{
	copyFrom(other);
}

JsonDataModel::JsonDataModel(JsonDataModel&& other)
{
	moveFrom(std::move(other));
}

JsonDataModel& JsonDataModel::operator=(const JsonDataModel& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}

	return *this;
}

JsonDataModel& JsonDataModel::operator=(JsonDataModel&& other)
{
	if (this != &other)
	{
		free();
		moveFrom(std::move(other));
	}

	return *this;
}

JsonDataModel::~JsonDataModel()
{
	free();
}

bool JsonDataModel::hasInstance() const
{
	return value != nullptr;
}

void JsonDataModel::print() const
{
	if (!hasInstance())
	{
		throw std::runtime_error("Cannot print uninitialized Json Data Model!");
	}

	value->writeFormatted(std::cout);
}
