#include "JsonNull.h"

JsonNull::JsonNull()
	: JsonNode(JsonNode::JsonNodeType::NullNode)
{

}

void JsonNull::writeNested(std::ostream& os, unsigned int nestingDepth) const
{
	static const char NULL_TEXT[] = "null";

	os << NULL_TEXT;
}

JsonNode* JsonNull::clone() const
{
	return new JsonNull(*this);
}
