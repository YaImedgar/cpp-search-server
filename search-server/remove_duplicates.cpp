#include "remove_duplicates.h"

using std::string_literals::operator""s;

void RemoveDuplicates(SearchServer& search_server)
{
	std::map<std::set<std::string>, std::vector<int>> doc_to_del;
	std::set<int> remove_docs;
	for (const int document_id : search_server)
	{
		std::set<std::string> words;
		std::map<std::string, double> word_with_freq = search_server.GetWordFrequencies(document_id);
		for (auto [word, freq] : word_with_freq)
		{
			words.insert(word);
		}
		
		if (doc_to_del.count(words) == 0)
		{
			doc_to_del[words].push_back(document_id);
		}
		else
		{
			remove_docs.insert(document_id);
		}
	}

	for (const int to_remove : remove_docs)
	{
		search_server.RemoveDocument(to_remove);
	}
}
