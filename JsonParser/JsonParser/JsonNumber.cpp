#include "JsonNumber.h"

JsonNumber::JsonNumber(double number)
	: JsonNode(JsonNode::JsonNodeType::NumberNode), value(number)
{

}
