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

void JsonObject::print(unsigned int nestingDepth) const
{
	static const char OPENING_BRACKET = '{';
	static const char CLOSING_BRACKET = '}';
	static const char MEMBER_SEPARATOR = ',';

	std::cout << OPENING_BRACKET << std::endl;

	for (size_t i = 0; i < count; i++)
	{
		printIndentation(nestingDepth + 1);
		values[i].print(nestingDepth + 1);
		
		if (i + 1 != count)
		{
			std::cout << MEMBER_SEPARATOR;
		}

		std::cout << std::endl;
	}

	printIndentation(nestingDepth);
	std::cout << CLOSING_BRACKET;
}

void JsonObject::addMember(const MyString& key, JsonNode* value)
{
	if (count == capacity)
	{
		resize(capacity * 2);
	}

	values[count++] = ObjectValue(key, value);
}

JsonNode* JsonObject::clone() const
{
	return new JsonObject(*this);
}

void JsonObject::ObjectValue::free()
{
	delete value;
}

void JsonObject::ObjectValue::copyFrom(const ObjectValue& other)
{
	key = other.key;
	value = other.value->clone();
}

void JsonObject::ObjectValue::moveFrom(ObjectValue&& other)
{
	key = other.key;
	value = other.value;

	other.value = nullptr;
	other.key = "";
}

JsonObject::ObjectValue::ObjectValue() : key(""), value(nullptr)
{

}

JsonObject::ObjectValue::ObjectValue(const MyString& key, JsonNode* value) : key(key), value(value)
{

}

JsonObject::ObjectValue::ObjectValue(const ObjectValue& other)
{
	copyFrom(other);
}

JsonObject::ObjectValue::ObjectValue(ObjectValue&& other)
{
	moveFrom(std::move(other));
}

JsonObject::ObjectValue& JsonObject::ObjectValue::operator=(const ObjectValue& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}

	return *this;
}

JsonObject::ObjectValue& JsonObject::ObjectValue::operator=(ObjectValue&& other)
{
	if (this != &other)
	{
		free();
		moveFrom(std::move(other));
	}

	return *this;
}

JsonObject::ObjectValue::~ObjectValue()
{
	free();
}

void JsonObject::ObjectValue::print(unsigned int nestingDepth) const
{
	static const char KEY_SEPARATOR = '"';

	std::cout << KEY_SEPARATOR << key << KEY_SEPARATOR << ": ";
	value->print(nestingDepth + 1);
}
