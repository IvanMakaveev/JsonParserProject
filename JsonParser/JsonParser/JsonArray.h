#pragma once
#include "JsonNode.h"

class JsonArray : public JsonNode
{
	JsonNode** values;
	size_t capacity;
	size_t count;

	void free();
	void copyFrom(const JsonArray& other);
	void moveFrom(JsonArray&& other);
	void resize(size_t newCapacity);

public:
	JsonArray();
	JsonArray(const JsonArray& other);
	JsonArray(JsonArray&& other);
	JsonArray& operator=(const JsonArray& other);
	JsonArray& operator=(JsonArray&& other);
	~JsonArray();

	JsonNode* clone() const override;
};

