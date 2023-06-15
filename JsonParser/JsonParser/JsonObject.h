#pragma once
#include "MyString.h"
#include "JsonNode.h"
#include "HelperFunctions.h"

class JsonObject : public JsonNode
{
	class ObjectValue
	{
		MyString key;
		JsonNode* value;

		void free();

		void copyFrom(const ObjectValue& other);

		void moveFrom(ObjectValue&& other);

	public:
		ObjectValue();
		ObjectValue(const MyString& key, JsonNode* value);
		ObjectValue(const ObjectValue& other);
		ObjectValue(ObjectValue&& other);
		ObjectValue& operator=(const ObjectValue& other);
		ObjectValue& operator=(ObjectValue&& other);
		~ObjectValue();

		void print(unsigned int nestingDepth) const;
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

	void print(unsigned int nestingDepth) const override;
	void addMember(const MyString& key, JsonNode* value);

	JsonNode* clone() const override;
};

