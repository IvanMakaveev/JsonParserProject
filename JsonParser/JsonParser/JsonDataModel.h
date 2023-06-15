#pragma once
#include "JsonNode.h"
#include "MyString.h"
#include "JsonArray.h"

class JsonDataModel
{
	JsonNode* value;
	bool containsInstance;

	void free();
	void copyFrom(const JsonDataModel& other);
	void moveFrom(JsonDataModel&& other);
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

	void search(const MyString& key) const
	{
		JsonArray result;
	}

	void set(const MyString& path, const MyString& text);
	void create(const MyString& path, const MyString& text);
	void deleteAt(const MyString& path);
	void move(const MyString& from, const MyString& to);
};

