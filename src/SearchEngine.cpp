#include "SearchEngine.h"

SearchServer::SearchServer(InvertedIndex& idx) : index(idx) { };

std::vector<std::vector<RelativeIndex>> SearchServer::search(const
	std::vector<std::string>& queries_input) const {
	std::vector<std::vector<RelativeIndex>> result;

	for (auto&& e : queries_input) {
        result.push_back(searchWord(e));
	}

	return result;
}

std::vector<RelativeIndex> SearchServer::searchWord(std::string searchString) const {
	std::vector<RelativeIndex> result(maxResponses);
	std::transform(searchString.begin(), searchString.end(), searchString.begin(), tolower);

	std::istringstream str(searchString);
	std::vector<std::string> words = { std::istream_iterator<std::string>(str), std::istream_iterator<std::string>() };
	std::unordered_map<size_t, float> relativeMap;
    float min = 0;

	for (auto& element : words) {
		for (auto& entry : index.getWordCount(element)) {
            relativeMap[entry.docId] += entry.count;
		}
	}

	if (relativeMap.empty())
		return {};

    for (auto&& element : relativeMap) {
        if (element.second > min) {
            RelativeIndex relativeIndex = { element.first, element.second };

            for (size_t i = 0, ie = result.size(); i != ie; ++i) {
                if (element.second > result[i].rank) {
                    result.insert(result.begin() + i, relativeIndex);
                    break;
                }
            }

            result.pop_back();
            min = result.back().rank;
        }
    }

    float max = result[0].rank;
    for (auto&& element : result) {
        element.rank /= max;
        std::stringstream ss;
        ss << std::setprecision(3) << element.rank;
        ss >> element.rank;
    }

	return result;
}

void SearchServer::setMaxResponses(int maxResponse) {
	maxResponses = maxResponse;
}