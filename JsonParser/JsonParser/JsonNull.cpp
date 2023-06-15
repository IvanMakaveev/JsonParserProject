#include "JsonNull.h"

JsonNull::JsonNull()
	: JsonNode(JsonNode::JsonNodeType::NullNode)
{

}

void JsonNull::print(unsigned int nestingDepth) const
{
	static const char NULL_TEXT[] = "null";

	std::cout << NULL_TEXT;
}

JsonNode* JsonNull::clone() const
{
	return new JsonNull(*this);
}
