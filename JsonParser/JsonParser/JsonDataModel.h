#pragma once
#include <sstream>
#include "JsonNode.h"
#include "MyString.h"
#include "JsonArray.h"
#include "JsonObject.h"
#include "Vector.hpp"
#include "HelperFunctions.h"


class JsonDataModel
{
	JsonNode* value;

	void free();
	void copyFrom(const JsonDataModel& other);
	void moveFrom(JsonDataModel&& other);

	MyString getNextPathElement(std::stringstream& pathStream)
	{
		static const char PATH_SEPARATOR = '/';
		static const size_t BUFFER_SIZE = 1024;
		static char elementId[BUFFER_SIZE] = { 0 };

		pathStream.getline(elementId, BUFFER_SIZE, PATH_SEPARATOR);
		return MyString(elementId);
	}

	JsonNode* getTarget(std::stringstream& pathStream)
	{
		JsonNode* nodeResult = value;

		while (true)
		{
			if (isCollectionNode(value))
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

	bool isCollectionNode(const JsonNode* nodeToCheck) const
	{
		return nodeToCheck->getType() == JsonNode::JsonNodeType::ArrayNode ||
			nodeToCheck->getType() == JsonNode::JsonNodeType::ObjectNode;
	}

	bool isRootPath(const MyString& path)
	{
		return path == "";
	}

public:
	JsonDataModel();
	JsonDataModel(JsonNode* value);
	JsonDataModel(const JsonDataModel& other);
	JsonDataModel(JsonDataModel&& other);
	JsonDataModel& operator=(const JsonDataModel& other);
	JsonDataModel& operator=(JsonDataModel&& other);
	~JsonDataModel();

	bool hasInstance() const;
	void print() const;

	Vector<const JsonNode*> search(const MyString& key) const
	{
		if (!hasInstance())
		{
			throw std::runtime_error("Cannot search in uninitialized Json Data Model!");
		}

		Vector<const JsonNode*> result;

		value->search(key, result);

		return result;
	}

	void set(const MyString& path, const JsonDataModel& model)
	{
		set(path, model.value->clone());
	}

	void set(const MyString& path, JsonDataModel&& tempModel)
	{
		set(path, tempModel.value);
		tempModel.value = nullptr;
	}

	void set(const MyString& path, JsonNode* nodeToSet)
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


	void create(const MyString& path, const JsonDataModel& model)
	{
		create(path, model.value->clone());
	}

	void create(const MyString& path, JsonDataModel&& tempModel)
	{
		create(path, tempModel.value);
		tempModel.value = nullptr;
	}

	void create(const MyString& path, JsonNode* nodeToAdd)
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
			static_cast<JsonObject*>(targetNode)->addMember(newId, nodeToAdd);
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

	void deleteAt(const MyString& path)
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

	JsonNode* getElementAt(const MyString& path)
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

	void move(const MyString& from, const MyString& to);

	void write(std::ostream& os) const
	{
		if (!hasInstance())
		{
			throw std::runtime_error("Cannot export uninitialized Json Data Model!");
		}

		value->writeFormatted(os);
	}
};

