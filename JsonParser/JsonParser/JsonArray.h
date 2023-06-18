#pragma once
#include "MyString.h"
#include "JsonCollection.h"
#include "HelperFunctions.h"

class JsonArray : public JsonCollection
{
	JsonNode** values;
	size_t capacity;
	size_t count;

	void free();
	void copyFrom(const JsonArray& other);
	void moveFrom(JsonArray&& other);
	void resize(size_t newCapacity);
	unsigned int getElementId(const MyString& key) const;
public:
	JsonArray();
	JsonArray(const JsonArray& other);
	JsonArray(JsonArray&& other);
	JsonArray& operator=(const JsonArray& other);
	JsonArray& operator=(JsonArray&& other);
	~JsonArray();

	void writeNested(std::ostream& os, unsigned int nestingDepth) const override;

	void search(const MyString& key, Vector<const JsonNode*>& result) const override
	{
		for (size_t i = 0; i < count; i++)
		{
			values[i]->search(key, result);
		}
	}

	void addElement(JsonNode* nodeToAdd);

	void deleteElement(const MyString& elementKey) override
	{
		size_t elementToRemove = getElementId(elementKey);

		if (elementToRemove >= count)
		{
			throw std::invalid_argument("Cannot delete an element with invalid array ID!");
		}

		delete values[elementToRemove];
		count--;
		for (size_t i = elementToRemove; i < count; i++)
		{
			values[i] = values[i + 1];
		}
	}

	void setElement(const MyString& elementKey, JsonNode* nodeToSet) override
	{
		if (nodeToSet == nullptr)
		{
			throw std::invalid_argument("Cannot set a node to nullptr");
		}

		size_t targetElement = getElementId(elementKey);
		if (targetElement >= count)
		{
			throw std::invalid_argument("Cannot set the value of an invalid array ID!");
		}

		delete values[targetElement];
		values[targetElement] = nodeToSet;
	}

	JsonNode* getChildElement(const MyString& elementKey) override
	{
		size_t targetElement = getElementId(elementKey);
		if (targetElement >= count)
		{
			throw std::invalid_argument("Cannot get the value of an invalid array ID!");
		}

		return values[targetElement];
	}

	JsonNode* clone() const override;
};

