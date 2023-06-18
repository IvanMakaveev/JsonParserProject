#include "SearchCommand.h"

SearchCommand::SearchCommand(const MyString& key) : searchKey(key)
{

}

void SearchCommand::execute(JsonDataModel& model)
{
	Vector<const JsonNode*> searchResults = model.search(searchKey);
	size_t elements = searchResults.getSize();

	std::cout << "Search results by keyword: " << searchKey << std::endl;
	std::cout << "[" << std::endl;
	for (size_t i = 0; i < elements; i++)
	{
		searchResults[i]->writeNested(std::cout, 1);

		if (i + 1 != elements)
		{
			std::cout << ',';
		}

		std::cout << std::endl;
	}
	std::cout << "]" << std::endl;
}
