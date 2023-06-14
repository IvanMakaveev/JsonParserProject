#include "JsonBool.h"

JsonBool::JsonBool(bool value)
	: JsonNode(JsonNode::JsonNodeType::BoolNode), value(value)
{

}

JsonNode* JsonBool::clone() const
{
	return new JsonBool(*this);
}
