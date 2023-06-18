#pragma once
#include "MyString.h"
#include "JsonCollection.h"

// JSON Array value node - container of JSON nodes
class JsonArray : public JsonCollection
{
	JsonNode** values;
	size_t capacity;
	size_t count;

	// Big 6 functionallity
	void free();
	void copyFrom(const JsonArray& other);
	void moveFrom(JsonArray&& other);

	// Private functionallity for working with the collection
	void resize(size_t newCapacity);
	unsigned int getElementId(const MyString& key) const;

public:
	// Big 6 interface
	JsonArray();
	JsonArray(const JsonArray& other);
	JsonArray(JsonArray&& other);
	JsonArray& operator=(const JsonArray& other);
	JsonArray& operator=(JsonArray&& other);
	~JsonArray();

	// Function overrides from base class JsonNode - printing and searching
	void writeNested(std::ostream& os, unsigned int nestingDepth) const override;
	void search(const MyString& key, Vector<const JsonNode*>& result) const override;

	// Adding element to the array
	void addElement(JsonNode* nodeToAdd);

	// Function overrides from class JsonCollection - collection operations
	void deleteElement(const MyString& elementKey) override;
	void setElement(const MyString& elementKey, JsonNode* nodeToSet) override;
	JsonNode* getChildElement(const MyString& elementKey) override;

	// Cloning
	JsonNode* clone() const override;
};

