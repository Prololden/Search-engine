#include "InvertedIndex.h"

freqType InvertedIndex::getFreqDict() {
	return freqDict;
}

void InvertedIndex::updateDocumentBase(std::vector<std::string> inputDocs) {
	std::vector<std::future<freqType>> result;
	BS::thread_pool pool;
	for (size_t i = 0, ie = inputDocs.size(); i != ie; ++i) {
		auto funcPool = pool.submit(
				&InvertedIndex::getWords,
				this,
				inputDocs[i],
				static_cast<int>(i)
				);
		result.push_back(std::move(funcPool));
	}
	for (size_t i = 0, ie = inputDocs.size(); i != ie; ++i) {
		auto r = result[i].get();
		for (auto&& item : r) {
			auto key = item.first;
			auto entryVec = item.second;
			freqDict[key].insert(freqDict[key].end(), entryVec.begin(), entryVec.end());
		}
	}
}
std::vector<Entry> InvertedIndex::getWordCount(const std::string& word) const {
	std::vector<Entry> result{};
	auto it = freqDict.find(word);
	if (it == freqDict.end())
		return result;
	for (auto e : it->second)
		result.push_back(e);
	return result;
}

freqType InvertedIndex::getWords(std::string filepath, int idDoc) const {
	try {
		if (!std::filesystem::exists(filepath))
			throw ExceptionFileNotFound();
	}
	catch (ExceptionFileNotFound e) {
		std::cerr << e.what() << std::endl;
		return freqType();
	}
	freqType result;
	std::ifstream file(filepath);
	if (file.is_open()) {
		std::istream_iterator<std::string> it(file);
		while (it != std::istream_iterator<std::string>()) {
			std::string word = *it;
			std::transform(word.begin(), word.end(), word.begin(), tolower);
			if (result.find(word) == result.end()) {
				result[word].push_back({ idDoc, 0 });
			}
			result[word][0].count++;
			it++;
		}
		file.close();
	}
	return result;
}