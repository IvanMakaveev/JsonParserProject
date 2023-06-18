#include "JsonNode.h"

JsonNode::JsonNode(JsonNodeType type) : type(type)
{

}

JsonNode::JsonNodeType JsonNode::getType() const
{
	return type;
}

void JsonNode::writeFormatted(std::ostream& os) const
{
	writeNested(os, 0);
}

void JsonNode::search(const MyString& key, Vector<const JsonNode*>& result) const
{
	return;
}
