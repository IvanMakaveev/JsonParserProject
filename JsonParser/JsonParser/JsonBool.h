#pragma once
#include "JsonNode.h"

// JSON Bool value node
class JsonBool : public JsonNode
{
	bool value;

public:
	JsonBool(bool value);

	void writeNested(std::ostream& os, unsigned int nestingDepth) const override;

	JsonNode* clone() const override;
};

