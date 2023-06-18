#pragma once
#include "MyString.h"
#include "Vector.hpp"
#include <iostream>

// Base abstract class for a JSON node in a tree structure
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

	// Printing functions for recursive printing
	virtual void writeNested(std::ostream& os, unsigned int nestingDepth) const = 0;
	void writeFormatted(std::ostream& os) const;

	// Function for recursive search of child elements
	virtual void search(const MyString& key, Vector<const JsonNode*>& result) const;

	// Virtual clone and destructor
	virtual JsonNode* clone() const = 0;
	virtual ~JsonNode() = default;
};

