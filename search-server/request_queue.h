#pragma once

#include "document.h"
#include "search_server.h"

#include <string>
#include <vector>
#include <deque>
#include <numeric>

class RequestQueue
{
public:
	explicit RequestQueue(const SearchServer& search_server);

	template <typename DocumentPredicate>
	std::vector<Document> AddFindRequest(const std::string& raw_query, DocumentPredicate document_predicate);
	std::vector<Document> AddFindRequest(const std::string& raw_query, DocumentStatus status);
	std::vector<Document> AddFindRequest(const std::string& raw_query);
	int GetNoResultRequests() const;

private:
	struct QueryResult
	{
		std::string query;
		int num_of_results;
	};
	const SearchServer& server_;
	std::deque<QueryResult> requests_;
	const static int min_in_day_ = 1440;
};

template <typename DocumentPredicate>
std::vector<Document> RequestQueue::AddFindRequest(const std::string& raw_query, DocumentPredicate document_predicate)
{
	std::vector<Document> search_result = server_.FindTopDocuments(raw_query, document_predicate);
	if (requests_.size() >= min_in_day_)
	{
		requests_.pop_front();
	}
	requests_.push_back({ raw_query, static_cast<int>(search_result.size()) });
	return search_result;
}
