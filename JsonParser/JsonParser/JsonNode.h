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

protected:

public:
	JsonNode(JsonNodeType type);
	JsonNodeType getType() const;

	virtual void print(unsigned int nestingDepth) const = 0;
	void print() const;

	virtual JsonNode* clone() const = 0;
	virtual ~JsonNode() = default;
};

