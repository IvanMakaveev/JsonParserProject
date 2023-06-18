#include "JsonNode.h"

/*
	Constructors and getters
*/

JsonNode::JsonNode(JsonNodeType type) : type(type)
{

}

JsonNode::JsonNodeType JsonNode::getType() const
{
	return type;
}

/*
	Printing interface function
*/

void JsonNode::writeFormatted(std::ostream& os) const
{
	writeNested(os, 0);
}

/*
	Parent definition of search function - by default elements don't have any children
*/

void JsonNode::search(const MyString& key, Vector<const JsonNode*>& result) const
{
	return;
}
