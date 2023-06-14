#pragma once
#include "MyString.h"
#include "JsonNode.h"

class JsonString : public JsonNode
{
	MyString value;

public:
	JsonString(const MyString& text);

	JsonNode* clone() const override;
};

