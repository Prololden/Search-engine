#include "../include/InvertedIndex.h"
#include "gtest/gtest.h"

TEST(InvertedIndex, updateDocumentBase) {
	std::string testString = "a b c d e f g h i j k";
	freqType freqDict;
	
	std::ofstream file("testIndex.txt");
	file << testString;
	file.close();
	std::istringstream s(testString);
	std::istream_iterator<std::string> it(s);
	while (it != std::istream_iterator<std::string>()) {
		freqDict[*it] = { { 0, 1 } };
		it++;
	}

	InvertedIndex idx;
	idx.updateDocumentBase({ "testIndex.txt" });

	std::remove("testIndex.txt");
	EXPECT_EQ(idx.getFreqDict(), freqDict);
}

TEST(InvertedIndex, getWordCount) {
	std::string testString = "a b c d e f g h i j k";
	freqType freqDict;

	std::ofstream file("testIndex0.txt");
	file << testString;
	file.close();

	file.open("testIndex1.txt");
	file << testString;
	file.close();

	file.open("testIndex2.txt");
	file << testString;
	file.close();

	file.open("testIndex3.txt");
	file << testString;
	file.close();

	InvertedIndex idx;
	idx.updateDocumentBase({
			"testIndex0.txt",
			"testIndex1.txt",
			"testIndex2.txt",
			"testIndex3.txt"
		});

	std::remove("testIndex0.txt");
	std::remove("testIndex1.txt");
	std::remove("testIndex2.txt");
	std::remove("testIndex3.txt");
	EXPECT_EQ(idx.getWordCount("a").size(), 4);
}

