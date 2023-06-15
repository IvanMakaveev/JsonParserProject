#include <iostream>
#include "JsonDataModel.h"
#include "JsonParser.h"

int main()
{
	std::ifstream ifs("read.json");

	JsonDataModel model = JsonParser().read(ifs);
	model.print();
}