#pragma once

class ExceptionConfigNotFound {
public:
	const char* what() {
		return "Config file not found.";
	}
};

class ExceptionRequestsNotFound {
public:
	const char* what() {
		return "Requests file not found.";
	}
};

class ExceptionFileNotFound {
public:
	const char* what() {
		return "File not found.";
	}
};

class ExceptionAnswersNotOpen {
public:
	const char* what() {
		return "answers.json cannot opened.";
	}
};

class ExceptionConfigEmpty {
public:
	const char* what() {
		return "Configure file is empty.";
	}
};

class ExceptionRequestsEmpty {
public:
	const char* what() {
		return "Requests file is empty.";
	}
};