#pragma once

class JsonNode
{
public:
	virtual void print() const = 0;

	virtual ~JsonNode() = default;
};

