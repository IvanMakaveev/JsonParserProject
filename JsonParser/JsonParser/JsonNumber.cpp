#include "JsonNumber.h"

JsonNumber::JsonNumber(double number)
	: JsonNode(JsonNode::JsonNodeType::NumberNode), value(number)
{

}

JsonNode* JsonNumber::clone() const
{
	return new JsonNumber(*this);
}
