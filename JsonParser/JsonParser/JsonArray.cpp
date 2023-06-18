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

unsigned int JsonArray::getElementId(const MyString& key) const
{
	if (key.length() != 1 || !isDigit(key[0]))
	{
		throw std::runtime_error("Cannot acces arrays with non-digit key!");
	}

	return toNumber(key[0]);
}

JsonArray::JsonArray() 
	: JsonCollection(JsonNode::JsonNodeType::ArrayNode), capacity(8), count(0)
{
	values = new JsonNode * [capacity];
}

JsonArray::JsonArray(const JsonArray& other) : JsonCollection(other)
{
	copyFrom(other);
}

JsonArray::JsonArray(JsonArray&& other) : JsonCollection(std::move(other))
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

void JsonArray::writeNested(std::ostream& os, unsigned int nestingDepth) const
{
	static const char OPENING_BRACKET = '[';
	static const char CLOSING_BRACKET = ']';
	static const char ELEMENT_SEPARATOR = ',';

	os << OPENING_BRACKET << std::endl;

	for (size_t i = 0; i < count; i++)
	{
		writeIndentation(os, nestingDepth + 1);
		values[i]->writeNested(os, nestingDepth + 1);

		if (i + 1 != count)
		{
			os << ELEMENT_SEPARATOR;
		}

		os << std::endl;
	}

	writeIndentation(os, nestingDepth);
	os << CLOSING_BRACKET;
}

void JsonArray::addElement(JsonNode* nodeToAdd)
{
	if (count == capacity)
	{
		resize(capacity * 2);
	}

	values[count++] = nodeToAdd;
}

JsonNode* JsonArray::clone() const
{
	return new JsonArray(*this);
}
