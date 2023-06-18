#pragma once
#include <sstream>
#include "JsonNode.h"
#include "MyString.h"
#include "Vector.hpp"

// A wrapper class providing the complete functionallity of a JSON Data Model
class JsonDataModel
{
	JsonNode* value;

	// Big 6 functionallity
	void free();
	void copyFrom(const JsonDataModel& other);
	void moveFrom(JsonDataModel&& other);

	// Private functions for data manipulation and validation
	MyString getNextPathElement(std::stringstream& pathStream);
	JsonNode* getTarget(std::stringstream& pathStream);
	bool isCollectionNode(const JsonNode* nodeToCheck) const;
	bool isRootPath(const MyString& path);

public:
	// Big 6 interface
	JsonDataModel();
	JsonDataModel(JsonNode* value);
	JsonDataModel(const JsonDataModel& other);
	JsonDataModel(JsonDataModel&& other);
	JsonDataModel& operator=(const JsonDataModel& other);
	JsonDataModel& operator=(JsonDataModel&& other);
	~JsonDataModel();

	// Validation function
	bool hasInstance() const;

	// Printing to console
	void print() const;

	// Searching for nodes
	Vector<const JsonNode*> search(const MyString& key) const;

	// Setting node value
	void set(const MyString& path, const JsonDataModel& model);
	void set(const MyString& path, JsonDataModel&& tempModel);
	void set(const MyString& path, JsonNode* nodeToSet);

	// Creating node
	void create(const MyString& path, const JsonDataModel& model);
	void create(const MyString& path, JsonDataModel&& tempModel);
	void create(const MyString& path, JsonNode* nodeToAdd);

	// Deleting node
	void deleteAt(const MyString& path);

	// Retrieving a node
	JsonNode* getElementAt(const MyString& path);

	// Moving a node
	void move(const MyString& from, const MyString& to);

	// Writing to file
	void write(std::ostream& os) const;
};

