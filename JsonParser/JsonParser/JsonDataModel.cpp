#include "JsonDataModel.h"

void JsonDataModel::free()
{
	delete value;
}

void JsonDataModel::copyFrom(const JsonDataModel& other)
{
	value = other.value->clone();
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
