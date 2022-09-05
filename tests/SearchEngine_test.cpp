#include "../include/SearchEngine.h"
#include "gtest/gtest.h"

TEST(SearchServer, search) {
	std::vector<std::string> requests {
		"test1",
		"test2",
		"test3"
	};
	std::vector<std::string> files;
	for (int i = 0; i < 3; ++i) {
		auto name = "testSearch" + std::to_string(i) + ".txt";
		files.push_back(name);
		std::ofstream file(name);
		for (int j = 0; j < 3; ++j) {
			file << requests[i] << " ";
		}
		file.close();
	}

	InvertedIndex idx;
	idx.updateDocumentBase(files);

	SearchServer searchServer(idx);
	searchServer.setMaxResponses(3);
	auto result = searchServer.search(requests);
	std::vector<std::vector<RelativeIndex>> excepted {
		{
			{0, 1.0f},
			{0, 0.0f},
			{0, 0.0f}
		},
		{
			{1, 1.0f},
			{0, 0.0f},
			{0, 0.0f}
		},
		{
			{2, 1.0f},
			{0, 0.0f},
			{0, 0.0f}
		},
	};
	for (auto& e : files) {
		std::remove(e.c_str());
	}
	EXPECT_EQ(result, excepted);
}