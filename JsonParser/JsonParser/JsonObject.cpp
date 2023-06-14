#include "JsonObject.h"

void JsonObject::free()
{
	delete[] values;
}

void JsonObject::copyFrom(const JsonObject& other)
{
	capacity = other.capacity;
	count = other.count;
	values = new ObjectValue[capacity];

	for (size_t i = 0; i < count; i++)
	{
		values[i] = other.values[i];
	}
}

void JsonObject::moveFrom(JsonObject&& other)
{
	capacity = other.capacity;
	count = other.count;
	values = other.values;

	other.values = nullptr;
	other.capacity = other.count = 0;
}

void JsonObject::resize(size_t newCapacity)
{
	if (newCapacity < count)
	{
		throw std::logic_error("An error has occured during resizing of JSON Object");
	}

	capacity = newCapacity;
	ObjectValue* newValues = new ObjectValue[capacity];

	for (size_t i = 0; i < count; i++)
	{
		newValues[i] = std::move(values[i]);
	}

	delete[] values;
	values = newValues;
}

JsonObject::JsonObject()
	: JsonNode(JsonNode::JsonNodeType::ObjectNode), capacity(8), count(0)
{
	values = new ObjectValue[capacity];
}

JsonObject::JsonObject(const JsonObject& other) : JsonNode(other)
{
	copyFrom(other);
}

JsonObject::JsonObject(JsonObject&& other) : JsonNode(std::move(other))
{
	moveFrom(std::move(other));
}

JsonObject& JsonObject::operator=(const JsonObject& other)
{
	if (this != &other)
	{
		JsonNode::operator=(other);
		free();
		copyFrom(other);
	}

	return *this;
}

JsonObject& JsonObject::operator=(JsonObject&& other)
{
	if (this != &other)
	{
		JsonNode::operator=(std::move(other));
		free();
		moveFrom(std::move(other));
	}

	return *this;
}

JsonObject::~JsonObject()
{
	free();
}
