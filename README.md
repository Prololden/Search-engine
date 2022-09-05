# Search Engine
Application for search text in files.
## Content
* [Description](#description)
* [Build](#build)
* [Methods](#mthods)
* [Starting](#starting)

### Description

Search engine for local files. The search is performed according to the specified parameters (config.json) and outputs the result to the final file "answers.json".

The principle of the search movement should be heard:
1. In the configuration file, before starting the application, the names are set
files, the search engine will be configured by subject.
2. The search engine must independently bypass all files and
index them so that later on any search query to find the most
relevant documents.
3. The user sets the request via the requests.json JSON file. The request is
a set of words to search for documents.
4. The query is transformed into a list of words.
5. The index looks for those documents that contain all these words.
6. Search results are ranked, sorted and given to the user,
the maximum number of possible documents in the response is set in
configuration file.
7. At the end, the program generates the answers.json file, in which it writes
searching results.

### Build

Step 1. Create build folder in project folder:

	mkdir build && cd build

Step 2. Build project with CMake:

	cmake .. && cmake --build . --config Release --target SearchEngine

As a result, the project file will be placed in the Release folder in the root directory. The test file will be placed in the tests/Release subdirectory.

Step 3. Start application:

    .\Release\SearchEngine

### Methods

#### ConverterJSON
- void readConfig(std::filesystem::path path) - opens the specified file as a settings file for the application. If the file has not been opened, the application will throw an ExceptionConfigNotFound exception
- void readRequests(std::filesystem::path path) - opens the specified file with search queries. If the file has not been opened, the application will throw an ExceptionRequestsNotFound exception
- int getResponsesLimit() const - returns the maximum number of responses for a single request. The default is 5
- std::vector<std::string> getRequests() const - returns a list of requests received in readRequest()
- std::vector<std::string> getFiles() const - returns a list of files from a config file
- bool isConfigOpen() const - returns true if the config file has been opened or false
- bool isRequestsOpen() const - returns true if the request file was opened or false
- void putAnswers(std::vector<std::vector<std::pair<int, float>>> answers) const - puts the search results in the file "answers.json"

#### InvertedIndex
- void updateDocumentBase(std::vector<std::string> inputDocs) - reads files received from the configuration file, creates a list of words, and also counts their number indexing by documents
- std::vector<Entry> getWordCount(const std::string& word) const - returns a list of indexes for the specified word, regardless of the document
- freqType getFreqDict() - returns a list of all indexed words

#### SearchServer
- std::vector<std::vector<RelativeIndex>> search(const std::vector<std::string>& queries_input) const - returns the result of a search by words, taking into account their relativity according to the internal formula
- void setMaxResponses(int maxResponse) - sets the maximum number per request

### Starting

To start using the application, create two files "config.json" and "reguests.json".

**config.json example**
	
	{
      "config": {
        "name": "SearchEngine",
        "version": "0.1",
        "max_responses": 7
      },
      "files": [
        "resources/text01.txt",
        "resources/text02.txt",
        "resources/text03.txt",
        "resources/text04.txt",
        "resources/text05.txt"
      ]
    }

**requests.json example**

    {
      "requests": [
        "curabitur",
        "in the",
        "non"
      ]
    }

Then run SearchEngine, the result of the application will be the file "answers.json" containing a list of found words and their relativity.
