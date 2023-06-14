#include "JsonString.h"

JsonString::JsonString(const MyString& text) 
	: JsonNode(JsonNode::JsonNodeType::StringNode), value(text)
{

}
