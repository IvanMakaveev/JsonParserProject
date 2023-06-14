#pragma once
#include "MyString.h"
#include "JsonNode.h"

class JsonObject : public JsonNode
{
	class ObjectValue
	{
		MyString key;
		JsonNode* value;
	};

	ObjectValue* values;
	size_t capacity;
	size_t count;

	void free();
	void copyFrom(const JsonObject& other);
	void moveFrom(JsonObject&& other);
	void resize(size_t newCapacity);

public:
	JsonObject();
	JsonObject(const JsonObject& other);
	JsonObject(JsonObject&& other);
	JsonObject& operator=(const JsonObject& other);
	JsonObject& operator=(JsonObject&& other);
	~JsonObject();
};

