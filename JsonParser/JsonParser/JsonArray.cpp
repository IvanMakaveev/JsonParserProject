#include "JsonArray.h"
#include <stdexcept>
#include "HelperFunctions.h"

/*
	Big 6 functionallity
*/

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

/*
	Resizing
*/

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

/*
	Parsing a given key to element id
*/

unsigned int JsonArray::getElementId(const MyString& key) const
{
	if (key.length() != 1 || !isDigit(key[0]))
	{
		throw std::runtime_error("Cannot acces arrays with non-digit key!");
	}

	return toNumber(key[0]);
}

/*
	Big 6 interface
*/

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

/*
	Writing to stream
*/

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

/*
	Searching recursively
*/

void JsonArray::search(const MyString& key, Vector<const JsonNode*>& result) const
{
	for (size_t i = 0; i < count; i++)
	{
		values[i]->search(key, result);
	}
}

/*
	Array element manipulation
*/

void JsonArray::addElement(JsonNode* nodeToAdd)
{
	if (count == capacity)
	{
		resize(capacity * 2);
	}

	values[count++] = nodeToAdd;
}

void JsonArray::deleteElement(const MyString& elementKey)
{
	size_t elementToRemove = getElementId(elementKey);

	if (elementToRemove >= count)
	{
		throw std::invalid_argument("Cannot delete an element with invalid array ID!");
	}

	delete values[elementToRemove];
	count--;
	for (size_t i = elementToRemove; i < count; i++)
	{
		values[i] = values[i + 1];
	}
}

void JsonArray::setElement(const MyString& elementKey, JsonNode* nodeToSet)
{
	if (nodeToSet == nullptr)
	{
		throw std::invalid_argument("Cannot set a node to nullptr");
	}

	size_t targetElement = getElementId(elementKey);
	if (targetElement >= count)
	{
		throw std::invalid_argument("Cannot set the value of an invalid array ID!");
	}

	delete values[targetElement];
	values[targetElement] = nodeToSet;
}

JsonNode* JsonArray::getChildElement(const MyString& elementKey)
{
	size_t targetElement = getElementId(elementKey);
	if (targetElement >= count)
	{
		throw std::invalid_argument("Cannot get the value of an invalid array ID!");
	}

	return values[targetElement];
}

void JsonArray::moveElementsTo(JsonCollection* otherCollection)
{
	for (size_t i = 0; i < count; i++)
	{
		otherCollection->addElement(toString(i), values[i]);
	}

	count = 0;
	capacity = 8;
	delete[] values;
	values = new JsonNode * [capacity];
}

void JsonArray::addElement(const MyString& elementKey, JsonNode* nodeToAdd)
{
	addElement(nodeToAdd);
}

/*
	Cloning
*/

JsonNode* JsonArray::clone() const
{
	return new JsonArray(*this);
}
