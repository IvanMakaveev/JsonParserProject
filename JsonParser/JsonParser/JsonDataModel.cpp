#include "JsonDataModel.h"

#include "JsonArray.h"
#include "JsonObject.h"
#include "HelperFunctions.h"

/*
	Big 6 functionallity
*/

void JsonDataModel::free()
{
	delete value;
	value = nullptr;
}

void JsonDataModel::copyFrom(const JsonDataModel& other)
{
	if (other.hasInstance())
	{
		value = other.value->clone();
	}
}

void JsonDataModel::moveFrom(JsonDataModel&& other)
{
	value = other.value;

	other.value = nullptr;
}

/*
	Path manipulation
*/

MyString JsonDataModel::getNextPathElement(std::stringstream& pathStream)
{
	static const char PATH_SEPARATOR = '/';
	static const size_t BUFFER_SIZE = 1024;
	static char elementId[BUFFER_SIZE] = { 0 };

	pathStream.getline(elementId, BUFFER_SIZE, PATH_SEPARATOR);
	return MyString(elementId);
}

JsonNode* JsonDataModel::getTarget(std::stringstream& pathStream)
{
	JsonNode* nodeResult = value;

	while (true)
	{
		if (!isCollectionNode(nodeResult))
		{
			throw std::runtime_error("Invalid path! No such element found");
		}

		size_t ptrLocation = pathStream.tellg();
		MyString pathElement = getNextPathElement(pathStream);

		if (pathStream.eof())
		{
			pathStream.seekg(ptrLocation);
			return nodeResult;
		}

		nodeResult = static_cast<JsonCollection*>(nodeResult)->getChildElement(pathElement);
	}

	return nodeResult;
}

/*
	Validation functions
*/

bool JsonDataModel::isCollectionNode(const JsonNode* nodeToCheck) const
{
	return nodeToCheck->getType() == JsonNode::JsonNodeType::ArrayNode ||
		nodeToCheck->getType() == JsonNode::JsonNodeType::ObjectNode;
}

bool JsonDataModel::isRootPath(const MyString& path)
{
	return path == "";
}

/*
	Big 6 interface
*/

JsonDataModel::JsonDataModel() : value(nullptr)
{

}

JsonDataModel::JsonDataModel(JsonNode* value) : value(value)
{

}

JsonDataModel::JsonDataModel(const JsonDataModel& other)
{
	copyFrom(other);
}

JsonDataModel::JsonDataModel(JsonDataModel&& other)
{
	moveFrom(std::move(other));
}

JsonDataModel& JsonDataModel::operator=(const JsonDataModel& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}

	return *this;
}

JsonDataModel& JsonDataModel::operator=(JsonDataModel&& other)
{
	if (this != &other)
	{
		free();
		moveFrom(std::move(other));
	}

	return *this;
}

JsonDataModel::~JsonDataModel()
{
	free();
}

/*
	Validator for intance presence
*/

bool JsonDataModel::hasInstance() const
{
	return value != nullptr;
}

/*
	Printing to console
*/

void JsonDataModel::print() const
{
	if (!hasInstance())
	{
		throw std::runtime_error("Cannot print uninitialized Json Data Model!");
	}

	value->writeFormatted(std::cout);
}

/*
	Searching for nodes
*/

Vector<const JsonNode*> JsonDataModel::search(const MyString& key) const
{
	if (!hasInstance())
	{
		throw std::runtime_error("Cannot search in uninitialized Json Data Model!");
	}

	Vector<const JsonNode*> result;

	value->search(key, result);

	return result;
}

/*
	Setting node value
*/

void JsonDataModel::set(const MyString& path, const JsonDataModel& model)
{
	set(path, model.value->clone());
}

void JsonDataModel::set(const MyString& path, JsonDataModel&& tempModel)
{
	set(path, tempModel.value);
	tempModel.value = nullptr;
}

void JsonDataModel::set(const MyString& path, JsonNode* nodeToSet)
{
	if (!hasInstance())
	{
		throw std::runtime_error("Cannot set members of uninitialized Json Data Model!");
	}

	if (nodeToSet == nullptr)
	{
		throw std::invalid_argument("Cannot set members to nullptr node!");
	}

	std::stringstream pathStream(path.c_str());
	JsonNode* targetNode = getTarget(pathStream);
	MyString elementId = getNextPathElement(pathStream);

	if (!isCollectionNode(targetNode))
	{
		throw std::runtime_error("Cannot set members of non-container Json Nodes!");
	}

	static_cast<JsonCollection*>(targetNode)->setElement(elementId, nodeToSet);
}

/*
	Creating node
*/

void JsonDataModel::create(const MyString& path, const JsonDataModel& model)
{
	create(path, model.value->clone());
}

void JsonDataModel::create(const MyString& path, JsonDataModel&& tempModel)
{
	create(path, tempModel.value);
	tempModel.value = nullptr;
}

void JsonDataModel::create(const MyString& path, JsonNode* nodeToAdd)
{
	if (!hasInstance())
	{
		throw std::runtime_error("Cannot create members of uninitialized Json Data Model!");
	}

	std::stringstream pathStream(path.c_str());
	JsonNode* targetNode = getTarget(pathStream);
	MyString newId = getNextPathElement(pathStream);

	if (!isCollectionNode(targetNode))
	{
		throw std::runtime_error("Cannot create members of non-container Json Nodes!");
	}

	if (targetNode->getType() == JsonNode::JsonNodeType::ObjectNode)
	{
		static_cast<JsonObject*>(targetNode)->addElement(newId, nodeToAdd);
	}
	else if (targetNode->getType() == JsonNode::JsonNodeType::ArrayNode)
	{
		static_cast<JsonArray*>(targetNode)->addElement(nodeToAdd);
	}
	else
	{
		throw std::logic_error("Unknown collection type recieved!");
	}
}

/*
	Deleting node
*/

void JsonDataModel::deleteAt(const MyString& path)
{
	if (!hasInstance())
	{
		throw std::runtime_error("Cannot delete members of uninitialized Json Data Model!");
	}

	if (isRootPath(path))
	{
		throw std::invalid_argument("Cannot delete the root Json Data Model!");
	}

	std::stringstream pathStream(path.c_str());
	JsonNode* targetNode = getTarget(pathStream);
	MyString elementId = getNextPathElement(pathStream);

	if (!isCollectionNode(targetNode))
	{
		throw std::runtime_error("Cannot delete members of non-container Json Nodes!");
	}

	static_cast<JsonCollection*>(targetNode)->deleteElement(elementId);
}

/*
	Moving node
*/

void JsonDataModel::move(const MyString& fromPath, const MyString& toPath)
{
	if (!hasInstance())
	{
		throw std::runtime_error("Cannot move members of uninitialized Json Data Model!");
	}

	if (isRootPath(fromPath))
	{
		throw std::invalid_argument("Cannot move from the root Json Data Model!");
	}

	JsonNode* destNode = getElementAt(toPath);

	if (!isCollectionNode(destNode))
	{
		throw std::runtime_error("The destination node must be a collection!");
	}

	JsonNode* srcNode = getElementAt(fromPath);

	if (!isCollectionNode(srcNode))
	{
		throw std::runtime_error("The source node must be a collection!");
	}

	static_cast<JsonCollection*>(srcNode)->moveElementsTo(static_cast<JsonCollection*>(destNode));
}

/*
	Retrieving node
*/

JsonNode* JsonDataModel::getElementAt(const MyString& path)
{
	if (!hasInstance())
	{
		throw std::runtime_error("Cannot get members of uninitialized Json Data Model!");
	}

	if (isRootPath(path))
	{
		return value;
	}

	std::stringstream pathStream(path.c_str());
	JsonNode* targetNode = getTarget(pathStream);
	MyString elementId = getNextPathElement(pathStream);

	if (!isCollectionNode(targetNode))
	{
		throw std::runtime_error("Cannot get members of non-container Json Nodes!");
	}

	return static_cast<JsonCollection*>(targetNode)->getChildElement(elementId);
}

/*
	Writing to file
*/

void JsonDataModel::write(std::ostream& os) const
{
	if (!hasInstance())
	{
		throw std::runtime_error("Cannot export uninitialized Json Data Model!");
	}

	value->writeFormatted(os);
}
