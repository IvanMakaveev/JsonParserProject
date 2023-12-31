#pragma once
#include "MyString.h"
#include "JsonNode.h"

// JSON String value node
class JsonString : public JsonNode
{
	MyString value;

public:
	JsonString(const MyString& text);

	void writeNested(std::ostream& os, unsigned int nestingDepth) const override;

	JsonNode* clone() const override;
};

