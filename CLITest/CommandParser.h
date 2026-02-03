#ifndef _CMD_PARSER_H
#define _CMD_PARSER_H

#include <memory>
#include <sstream>

#include "ArgumentsParser.h"

class CommandParser : public Parser {
private:

	ConsoleReader* consoleReader;

	ArgumentsParser* argsParser;

	FileParser* fileParser;

	bool inputTaken;
	bool outputAppend;

	bool errorFlag;

public:
	CommandParser(ConsoleReader* CR, ArgumentsParser* AR, FileParser* FP)
		: consoleReader(CR), argsParser(AR), fileParser(FP),
		errorFlag(false), inputTaken(false), outputAppend(false), Parser() {};
	~CommandParser() {
		if (consoleReader) {
			delete(consoleReader);
		}
		if (argsParser) {
			delete(argsParser);
		}
		if (fileParser) {
			delete(fileParser);
		}
	}

	virtual void Parse() override;

	ConsoleReader* getConsoleReader();
};


#endif
