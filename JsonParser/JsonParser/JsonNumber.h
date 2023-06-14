#pragma once
#include "JsonNode.h"

class JsonNumber : public JsonNode
{
	double value;

public:
	JsonNumber(double number);

	void print(unsigned int nestingDepth) const override;

	JsonNode* clone() const override;
};

