#pragma once
#include "JsonNode.h"

// JSON Null value node
class JsonNull : public JsonNode
{
public:
	JsonNull();

	void writeNested(std::ostream& os, unsigned int nestingDepth) const override;

	JsonNode* clone() const override;
};

