#include "ConverterJSON.h"

ConverterJSON::ConverterJSON() : isCfgOpen(false), isReqOpen(false) { };

std::vector<std::string> ConverterJSON::getRequests() const {
	return requests;
}

std::vector<std::string> ConverterJSON::getFiles() const {
	return { config["files"].begin(), config["files"].end() };
}

int ConverterJSON::getResponsesLimit() const {
	const int defaultLimit = 5; // if not set in config.json default limit 5
	return config["config"]["max_responses"].is_null() ? defaultLimit : config["config"]["max_responses"].get<int>();
}

void ConverterJSON::putAnswers(
		std::vector<std::vector<std::pair<int, float>>> answers
	) const {
	json data;
	for (size_t i = 0, ie = answers.size(); i != ie; ++i) {
		std::ostringstream ss;
		ss << "request" << std::setw(3) << std::setfill('0') << i;
		std::string reqId(ss.str());

		if (answers[i].empty())
			data["answers"][reqId]["result"] = "false";
		else {
			data["answers"][reqId]["result"] = "true";
			for (const auto& element : answers[i]) {
				if (element.second > 0.0)
					data["answers"][reqId]["relevance"] += { {"doc_id", element.first}, { "rank", element.second }};
			}
		}
	}

	std::ofstream file("answers.json");
	if (!file.is_open()) {
		throw ExceptionAnswersNotOpen();
	}
	file << data.dump(4);
	file.close();
}

void ConverterJSON::readConfig(std::filesystem::path path) {
	try {
		if (!std::filesystem::exists(path))
			throw ExceptionConfigNotFound();
	}
	catch (ExceptionConfigNotFound e) {
		std::cerr << e.what() << std::endl;
		return;
	}
	std::ifstream file(path);
	if (file.is_open()) {
		isCfgOpen = true;
		file >> config;
		file.close();
		if (config.empty()) {
			throw ExceptionConfigEmpty();
		}
	}
}

void ConverterJSON::readRequests(std::filesystem::path path) {
	try {
		if (!std::filesystem::exists(path))
			throw ExceptionRequestsNotFound();
	}
	catch (ExceptionRequestsNotFound e) {
		std::cerr << e.what() << std::endl;
		return;
	}
	std::ifstream file(path);
	if (file.is_open()) {
		isReqOpen = true;
		json _requests;
		file >> _requests;
		file.close();
		if (_requests.empty()) {
			throw ExceptionRequestsEmpty();
		}
		requests = { _requests["requests"].begin(), _requests["requests"].end() };
	}
}

bool ConverterJSON::isConfigOpen() const {
	return isCfgOpen;
}

bool ConverterJSON::isRequestsOpen() const {
	return isReqOpen;
}