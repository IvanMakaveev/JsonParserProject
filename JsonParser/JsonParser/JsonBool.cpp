#include "JsonBool.h"

JsonBool::JsonBool(bool value)
	: JsonNode(JsonNode::JsonNodeType::BoolNode), value(value)
{

}

void JsonBool::print(unsigned int nestingDepth) const
{
	static const char TRUE_TEXT[] = "true";
	static const char FALSE_TEXT[] = "false";

	std::cout << (value ? TRUE_TEXT : FALSE_TEXT) << std::endl;
}

JsonNode* JsonBool::clone() const
{
	return new JsonBool(*this);
}
