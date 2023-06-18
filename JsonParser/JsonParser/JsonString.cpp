#include "JsonString.h"

JsonString::JsonString(const MyString& text) 
	: JsonNode(JsonNode::JsonNodeType::StringNode), value(text)
{

}

void JsonString::writeNested(std::ostream& os, unsigned int nestingDepth) const
{
	static const char STRING_SEPARATOR = '"';

	os << STRING_SEPARATOR << value << STRING_SEPARATOR;
}

JsonNode* JsonString::clone() const
{
	return new JsonString(*this);
}
