#pragma once
#include "MyString.h"

class JsonNode
{
public:
	enum class JsonNodeType
	{
		StringNode,
		BoolNode,
		NumberNode,
		NullNode,
		ArrayNode,
		ObjectNode
	};

private:

	JsonNodeType type;

public:
	JsonNode(JsonNodeType type);
	JsonNodeType getType() const;

	//virtual void print() const = 0;

	virtual JsonNode* clone() const = 0;
	virtual ~JsonNode() = default;
};

