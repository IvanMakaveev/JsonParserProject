#pragma once
#include "JsonNode.h"

// Abstract interface for providing collection functionallity
class JsonCollection : public JsonNode
{
public:
	JsonCollection(JsonNode::JsonNodeType type);

	// Interface abstract functions
	virtual JsonNode* getChildElement(const MyString& elementKey) = 0;
	virtual void deleteElement(const MyString& elementKey) = 0;
	virtual void setElement(const MyString& elementKey, JsonNode* nodeToSet) = 0;
	virtual void moveElementsTo(JsonCollection* otherCollection) = 0;
	virtual void addElement(const MyString& elementKey, JsonNode* nodeToSet) = 0;
};

