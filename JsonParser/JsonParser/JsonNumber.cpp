#include "JsonNumber.h"

JsonNumber::JsonNumber(double number)
	: JsonNode(JsonNode::JsonNodeType::NumberNode), value(number)
{

}

void JsonNumber::writeNested(std::ostream& os, unsigned int nestingDepth) const
{
	os << value;
}

JsonNode* JsonNumber::clone() const
{
	return new JsonNumber(*this);
}
