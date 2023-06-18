#include "JsonBool.h"

JsonBool::JsonBool(bool value)
	: JsonNode(JsonNode::JsonNodeType::BoolNode), value(value)
{

}

void JsonBool::writeNested(std::ostream& os, unsigned int nestingDepth) const
{
	static const char TRUE_TEXT[] = "true";
	static const char FALSE_TEXT[] = "false";

	os << (value ? TRUE_TEXT : FALSE_TEXT);
}

JsonNode* JsonBool::clone() const
{
	return new JsonBool(*this);
}
