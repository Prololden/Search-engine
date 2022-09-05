#include "../include/ConverterJSON.h"
#include "gtest/gtest.h"

TEST(ConverterJSON, readConfig) {
	json data;
	data["config"]["max_responses"] = 65655;
	std::ofstream file("testConfig.json");
	file << data;
	file.close();

	ConverterJSON converterJson;
	converterJson.readConfig("testConfig.json");
	std::remove("testConfig.json");
	EXPECT_EQ(converterJson.isConfigOpen(), true);
}

TEST(ConverterJSON, readRequests) {
	json data;
	data["config"]["max_responses"] = 65655;
	std::ofstream file("testRequests.json");
	file << data;
	file.close();

	ConverterJSON converterJson;
	converterJson.readRequests("testRequests.json");
	std::remove("testRequests.json");
	EXPECT_EQ(converterJson.isRequestsOpen(), true);
}

TEST(ConverterJSON, getResponsesLimit) {
	json data;
	data["config"]["max_responses"] = 65655;
	std::ofstream file("testConfig.json");
	file << data;
	file.close();

	ConverterJSON converterJson;
	converterJson.readConfig("testConfig.json");
	int maxResponses = converterJson.getResponsesLimit();
	std::remove("testConfig.json");
	EXPECT_EQ(maxResponses, 65655);
}

TEST(ConverterJSON, getRequests) {
	std::vector<std::string> req {
		"test",
		"test2",
		"test3"
	};
	json data;
	data["requests"] = req;
	std::ofstream file("testRequests.json");
	file << data;
	file.close();

	ConverterJSON converterJson;
	converterJson.readRequests("testRequests.json");
	auto requests = converterJson.getRequests();
	std::remove("testRequests.json");
	EXPECT_EQ(requests, req);
}

TEST(ConverterJSON, getFiles) {
	std::vector<std::string> files {
		"files/text0.txt",
		"files/text1.txt",
		"files/text2.txt",
		"files/text3.txt",
		"files/text4.txt",
		"files/text5.txt",
	};
	json data;
	data["files"] = files;
	std::ofstream file("testConfig.json");
	file << data;
	file.close();

	ConverterJSON converterJson;
	converterJson.readConfig("testConfig.json");
	auto testFiles = converterJson.getFiles();
	std::remove("testConfig.json");
	EXPECT_EQ(testFiles, files);
}

TEST(ConverterJSON, putAnswers) {
	std::vector<std::vector<std::pair<int, float>>> answers {
			{
				{1, 1.0f},
				{3, 1.0f},
				{0, 0.5f},
				{4, 0.5f}
			},
			{
				{1, 1.0f},
				{4, 1.0f},
				{3, 0.6669999957084656f}
			},
			{
				{1, 1.0f},
				{3, 1.0f},
				{0, 0.5f},
				{2, 0.5f}
			}
		};
	json data = R"({
		"answers": {
			"request000": {
				"relevance": [
					{
						"doc_id": 1,
						"rank": 1.0
					},
					{
						"doc_id": 3,
						"rank": 1.0
					},
					{
						"doc_id": 0,
						"rank": 0.5
					},
					{
						"doc_id": 4,
						"rank": 0.5
					}
				],
				"result": "true"
			},
			"request001": {
				"relevance": [
					{
						"doc_id": 1,
						"rank": 1.0
					},
					{
						"doc_id": 4,
						"rank": 1.0
					},
					{
						"doc_id": 3,
						"rank": 0.6669999957084656
					}
				],
				"result": "true"
			},
			"request002": {
				"relevance": [
					{
						"doc_id": 1,
						"rank": 1.0
					},
					{
						"doc_id": 3,
						"rank": 1.0
					},
					{
						"doc_id": 0,
						"rank": 0.5
					},
					{
						"doc_id": 2,
						"rank": 0.5
					}
				],
				"result": "true"
			}
		}
	})"_json;

	ConverterJSON converterJson;
	converterJson.putAnswers(answers);
	json result;
	std::ifstream file("answers.json");
	file >> result;
	file.close();
	std::remove("answers.json");
	EXPECT_EQ(result, data);
}