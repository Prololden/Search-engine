#pragma once
#include "InvertedIndex.h"
#include <filesystem>
#include <iterator>
#include <map>
#include <nlohmann/json.hpp>
#include <algorithm>

using json = nlohmann::json;

struct RelativeIndex {
	size_t docId;
	float rank;
	bool operator ==(const RelativeIndex& other) const {
		return (docId == other.docId && rank == other.rank);
	}
};
class SearchServer {
public:
	SearchServer() = delete;
	SearchServer(InvertedIndex& idx);
	std::vector<std::vector<RelativeIndex>> search(const
		std::vector<std::string>& queries_input) const;
	void setMaxResponses(int maxResponse);
private:
	std::vector<RelativeIndex> searchWord(std::string searchString) const;
	InvertedIndex index;
	int maxResponses = 5;
};