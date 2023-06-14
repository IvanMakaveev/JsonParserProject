#include "JsonArray.h"
#include <stdexcept>

void JsonArray::free()
{
	for (size_t i = 0; i < count; i++)
	{
		delete values[i];
	}

	delete[] values;
}

void JsonArray::copyFrom(const JsonArray& other)
{
	count = other.count;
	capacity = other.capacity;

	values = new JsonNode * [capacity];
	for (size_t i = 0; i < count; i++)
	{
		values[i] = other.values[i]->clone();
	}
}

void JsonArray::moveFrom(JsonArray&& other)
{
	count = other.count;
	capacity = other.capacity;
	values = other.values;

	other.values = nullptr;
	other.count = other.capacity = 0;
}

void JsonArray::resize(size_t newCapacity)
{
	if (newCapacity < count)
	{
		throw std::logic_error("An error has occured during resizing of JSON Array");
	}

	capacity = newCapacity;
	JsonNode** newNodes = new JsonNode * [capacity];

	for (size_t i = 0; i < count; i++)
	{
		newNodes[i] = values[i];
	}

	delete[] values;
	values = newNodes;
}

JsonArray::JsonArray() 
	: JsonNode(JsonNode::JsonNodeType::ArrayNode), capacity(8), count(0)
{
	values = new JsonNode * [capacity];
}

JsonArray::JsonArray(const JsonArray& other) : JsonNode(other)
{
	copyFrom(other);
}

JsonArray::JsonArray(JsonArray&& other) : JsonNode(std::move(other))
{
	moveFrom(std::move(other));
}

JsonArray& JsonArray::operator=(const JsonArray& other)
{
	if (this != &other)
	{
		JsonNode::operator=(other);
		free();
		copyFrom(other);
	}

	return *this;
}

JsonArray& JsonArray::operator=(JsonArray&& other)
{
	if (this != &other)
	{
		JsonNode::operator=(std::move(other));
		free();
		moveFrom(std::move(other));
	}

	return *this;
}

JsonArray::~JsonArray()
{
	free();
}
