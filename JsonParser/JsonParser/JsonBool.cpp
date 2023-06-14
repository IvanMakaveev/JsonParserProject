#include "JsonBool.h"

JsonBool::JsonBool(bool value)
	: JsonNode(JsonNode::JsonNodeType::BoolNode), value(value)
{

}
