#pragma once
#include "MyString.h"
#include "JsonNode.h"

class JsonString : public JsonNode
{
	MyString value;

public:
	JsonString(const MyString& text);

	void print(unsigned int nestingDepth) const override;

	JsonNode* clone() const override;
};

