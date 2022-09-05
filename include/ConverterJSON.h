#pragma once

#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <filesystem>
#include <nlohmann/json.hpp>
#include "customExceptions.h"

using json = nlohmann::json;

class ConverterJSON {
public:
	ConverterJSON();
	void readConfig(std::filesystem::path path);
	void readRequests(std::filesystem::path path);
	int getResponsesLimit() const;
	std::vector<std::string> getRequests() const;
	std::vector<std::string> getFiles() const;
	bool isConfigOpen() const;
	bool isRequestsOpen() const;
	void putAnswers(std::vector<std::vector<std::pair<int, float>>>
		answers) const;
private:
	bool isCfgOpen, isReqOpen;
	json config;
	std::vector<std::string> requests;
	json answers;
};