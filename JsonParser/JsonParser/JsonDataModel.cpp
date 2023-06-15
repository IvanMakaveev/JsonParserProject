#include "JsonDataModel.h"

void JsonDataModel::free()
{
	delete value;
	value = nullptr;
}

void JsonDataModel::copyFrom(const JsonDataModel& other)
{
	hasInstance = other.hasInstance;

	if (other.hasInstance)
	{
		value = other.value->clone();
	}
}

void JsonDataModel::moveFrom(JsonDataModel&& other)
{
	value = other.value;
	hasInstance = other.hasInstance;

	other.value = nullptr;
	other.hasInstance = false;
}

JsonDataModel::JsonDataModel() : value(nullptr), hasInstance(false)
{

}

JsonDataModel::JsonDataModel(JsonNode* value) : value(value)
{
	hasInstance = value != nullptr;
}

JsonDataModel::JsonDataModel(const JsonDataModel& other)
{
	copyFrom(other);
}

JsonDataModel::JsonDataModel(JsonDataModel&& other)
{
	std::move(other);
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
	return containsInstance;
}

void JsonDataModel::print() const
{
	value->print();
}
