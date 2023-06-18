#pragma once
#include "MyString.h"
#include "JsonCollection.h"
#include "HelperFunctions.h"

class JsonObject : public JsonCollection
{
	class ObjectValue
	{
		MyString key;
		JsonNode* value;

		void free();
		void copyFrom(const ObjectValue& other);
		void moveFrom(ObjectValue&& other);
	public:
		ObjectValue();
		ObjectValue(const MyString& key, JsonNode* value);
		ObjectValue(const ObjectValue& other);
		ObjectValue(ObjectValue&& other);
		ObjectValue& operator=(const ObjectValue& other);
		ObjectValue& operator=(ObjectValue&& other);
		~ObjectValue();

		void write(std::ostream& os, unsigned int nestingDepth) const;
		const MyString& getKey() const;
		JsonNode* getValue();
	};

	ObjectValue* values;
	size_t capacity;
	size_t count;

	void free();
	void copyFrom(const JsonObject& other);
	void moveFrom(JsonObject&& other);
	void resize(size_t newCapacity);
	int getMemberIndex(const MyString& elementKey) const
	{
		for (int i = 0; i < count; i++)
		{
			if (values[i].getKey() == elementKey)
			{
				return i;
			}
		}

		return -1;
	}
public:
	JsonObject();
	JsonObject(const JsonObject& other);
	JsonObject(JsonObject&& other);
	JsonObject& operator=(const JsonObject& other);
	JsonObject& operator=(JsonObject&& other);
	~JsonObject();

	void writeNested(std::ostream& os, unsigned int nestingDepth) const override;
	void addMember(const MyString& key, JsonNode* value);

	void search(const MyString& key, Vector<const JsonNode*>& result) const override
	{
		for (size_t i = 0; i < count; i++)
		{
			if (values[i].getKey() == key)
			{
				result.pushBack(values[i].getValue());
			}

			values[i].getValue()->search(key, result);
		}
	}

	void deleteElement(const MyString& elementKey) override
	{
		int memberIndex = getMemberIndex(elementKey);
		if (memberIndex == -1)
		{
			throw std::invalid_argument("Cannot delete member of invalid member key!");
		}

		count--;
		for (size_t i = memberIndex; i < count; i++)
		{
			values[i] = values[i + 1];
		}
	}

	void setElement(const MyString& elementKey, JsonNode* nodeToSet) override
	{
		if (nodeToSet == nullptr)
		{
			throw std::invalid_argument("Cannot set a node to nullptr/missing value!");
		}

		int memberIndex = getMemberIndex(elementKey);
		if (memberIndex == -1)
		{
			throw std::invalid_argument("Cannot delete member with invalid member key!");
		}

		values[memberIndex] = std::move(ObjectValue(elementKey, nodeToSet));
	}

	JsonNode* getChildElement(const MyString& elementKey) override
	{
		int memberIndex = getMemberIndex(elementKey);

		if (memberIndex == -1)
		{
			throw std::invalid_argument("Incorrect object member key! Cannot follow the given path!");
		}

		return values[memberIndex].getValue();
	}

	JsonNode* clone() const override;
};

