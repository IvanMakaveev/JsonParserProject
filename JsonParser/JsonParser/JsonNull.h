#pragma once
#include "JsonNode.h"

class JsonNull : public JsonNode
{
public:
	JsonNull();

	JsonNode* clone() const override;
};
