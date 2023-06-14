#include "JsonNull.h"

JsonNull::JsonNull()
	: JsonNode(JsonNode::JsonNodeType::NullNode)
{

}

void JsonNull::print(unsigned int nestingDepth) const
{
	std::cout << "null" << std::endl;
}

JsonNode* JsonNull::clone() const
{
	return new JsonNull(*this);
}
