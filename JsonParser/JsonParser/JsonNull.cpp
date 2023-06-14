#include "JsonNull.h"

JsonNull::JsonNull()
	: JsonNode(JsonNode::JsonNodeType::NullNode)
{

}

JsonNode* JsonNull::clone() const
{
	return new JsonNull(*this);
}
