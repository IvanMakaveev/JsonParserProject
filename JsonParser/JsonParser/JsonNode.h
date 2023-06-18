#pragma once
#include "MyString.h"
#include "Vector.hpp"
#include <iostream>

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

	virtual void writeNested(std::ostream& os, unsigned int nestingDepth) const = 0;
	void writeFormatted(std::ostream& os) const;

	virtual void search(const MyString& key, Vector<const JsonNode*>& result) const;

	virtual JsonNode* clone() const = 0;
	virtual ~JsonNode() = default;
};

