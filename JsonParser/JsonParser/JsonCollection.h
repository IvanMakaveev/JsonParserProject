#pragma once
#include "JsonNode.h"

class JsonCollection : public JsonNode
{
public:
	JsonCollection(JsonNode::JsonNodeType type);

	virtual JsonNode* getChildElement(const MyString& elementKey) = 0;
	virtual void deleteElement(const MyString& elementKey) = 0;
	virtual void setElement(const MyString& elementKey, JsonNode* nodeToSet) = 0;
};

