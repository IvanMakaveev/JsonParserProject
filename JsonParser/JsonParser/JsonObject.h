#pragma once
#include "MyString.h"
#include "JsonCollection.h"

// JSON Object value node - container of JSON Key-Value pairs
class JsonObject : public JsonCollection
{
	// Key-Value pair nested class used inside of the JsonObject
	class ObjectValue
	{
		MyString key;
		JsonNode* value;

		// Big 6 functionallity
		void free();
		void copyFrom(const ObjectValue& other);
		void moveFrom(ObjectValue&& other);
	public:
		// Big 6 interface
		ObjectValue();
		ObjectValue(const MyString& key, JsonNode* value);
		ObjectValue(const ObjectValue& other);
		ObjectValue(ObjectValue&& other);
		ObjectValue& operator=(const ObjectValue& other);
		ObjectValue& operator=(ObjectValue&& other);
		~ObjectValue();

		// Writing to stream
		void write(std::ostream& os, unsigned int nestingDepth) const;

		// Getters
		const MyString& getKey() const;
		JsonNode* getValue();
	};

	ObjectValue* values;
	size_t capacity;
	size_t count;

	// Big 6 functionallity
	void free();
	void copyFrom(const JsonObject& other);
	void moveFrom(JsonObject&& other);

	// Private functionallity for working with the collection
	void resize(size_t newCapacity);
	int getMemberIndex(const MyString& elementKey) const;

public:
	// Big 6 interface
	JsonObject();
	JsonObject(const JsonObject& other);
	JsonObject(JsonObject&& other);
	JsonObject& operator=(const JsonObject& other);
	JsonObject& operator=(JsonObject&& other);
	~JsonObject();

	// Function overrides from base class JsonNode - printing and searching
	void writeNested(std::ostream& os, unsigned int nestingDepth) const override;
	void search(const MyString& key, Vector<const JsonNode*>& result) const override;
	
	// Adding member to the object
	void addMember(const MyString& key, JsonNode* value);

	// Function overrides from class JsonCollection - collection operations
	void deleteElement(const MyString& elementKey) override;
	void setElement(const MyString& elementKey, JsonNode* nodeToSet) override;
	JsonNode* getChildElement(const MyString& elementKey) override;

	// Cloning
	JsonNode* clone() const override;
};

