#pragma once
#include "JsonNode.h"

class JsonBool : public JsonNode
{
	bool value;

public:
	JsonBool(bool value);

	void writeNested(std::ostream& os, unsigned int nestingDepth) const override;

	JsonNode* clone() const override;
};

