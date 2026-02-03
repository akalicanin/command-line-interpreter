#ifndef _ARGS_PARSER_H
#define _ARGS_PARSER_H

#include <memory>
#include <sstream>
#include <set>
#include <unordered_map>
#include <functional>

#include "FileParser.h"

class ArgumentsParser : public Parser {
private:
	FileParser* fileParser;

public:

	std::set<std::string> commandNames = { "echo", "wc", "prompt", "end", "time", "date", "touch",
										"truncate", "batch", "touch", "rm", "head" };

	std::set<std::string> commandOpts = { "-w", "-c", "-ncount" };

	ArgumentsParser()
		: fileParser(new FileParser(new FileReader)), Parser() {};

	~ArgumentsParser() {};

	virtual void Parse() override;

	std::string parseName(std::istringstream& stream);

	std::string parseOpt(std::istringstream& stream);

	std::string parseMultiLineInput(std::istringstream& stream, bool& inputTaken);

	std::string parseArguments(std::istringstream& stream, bool& inputTaken);

	std::string parseStringArg(std::istringstream& stream, bool& inputTaken);

	std::string parseFilenameArg(std::istringstream& stream, bool& inputTaken);

	std::string parseInputRedirection(std::istringstream& stream, bool& inputTaken);

	std::string parseOutputRedirection(std::istringstream& stream, bool& outputAppend);

	FileParser* getFileParser();
};


#endif
