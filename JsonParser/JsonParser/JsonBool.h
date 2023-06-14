#pragma once
#include "JsonNode.h"

class JsonBool : public JsonNode
{
	bool value;

public:
	JsonBool(bool value);
};

