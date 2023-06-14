#include "JsonNode.h"

JsonNode::JsonNode(JsonNodeType type) : type(type)
{

}

JsonNode::JsonNodeType JsonNode::getType() const
{
	return type;
}
