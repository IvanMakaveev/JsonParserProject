#pragma once
#include "JsonNode.h"

class JsonNull : public JsonNode
{

public:
	JsonNull();

	void print(unsigned int nestingDepth) const override;

	JsonNode* clone() const override;
};

