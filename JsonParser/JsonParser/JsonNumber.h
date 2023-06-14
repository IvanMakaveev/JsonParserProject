#pragma once
#include "JsonNode.h"

class JsonNumber : public JsonNode
{
	double value;

public:
	JsonNumber(double number);
};

