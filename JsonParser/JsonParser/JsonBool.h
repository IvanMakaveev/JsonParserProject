#pragma once
#include "JsonNode.h"

class JsonBool : public JsonNode
{
	bool value;

public:
	JsonBool(bool value);

	void print(unsigned int nestingDepth) const override;

	JsonNode* clone() const override;
};

