#include "JsonNode.h"

JsonNode::JsonNode(JsonNodeType type) : type(type)
{

}

JsonNode::JsonNodeType JsonNode::getType() const
{
	return type;
}

void JsonNode::print() const
{
	print(0);
}
