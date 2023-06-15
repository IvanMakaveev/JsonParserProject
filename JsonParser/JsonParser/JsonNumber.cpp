#include "JsonNumber.h"

JsonNumber::JsonNumber(double number)
	: JsonNode(JsonNode::JsonNodeType::NumberNode), value(number)
{

}

void JsonNumber::print(unsigned int nestingDepth) const
{
	std::cout << value;
}

JsonNode* JsonNumber::clone() const
{
	return new JsonNumber(*this);
}
