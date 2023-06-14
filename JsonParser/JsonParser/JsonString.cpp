#include "JsonString.h"

JsonString::JsonString(const MyString& text) 
	: JsonNode(JsonNode::JsonNodeType::StringNode), value(text)
{

}

void JsonString::print(unsigned int nestingDepth) const
{
	static const char STRING_SEPARATOR = '"';

	std::cout << STRING_SEPARATOR << value << STRING_SEPARATOR << std::endl;
}

JsonNode* JsonString::clone() const
{
	return new JsonString(*this);
}
