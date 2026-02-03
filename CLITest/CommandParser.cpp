#include "CommandParser.h"

#include <memory>
#include <sstream>
#include <iostream>

void CommandParser::Parse() {
	std::string* line = this->getConsoleReader()->ReadLine(); // "echo "Hello World""
	std::istringstream stream(*line);
	inputTaken = false;
	outputAppend = false;

	std::string name = argsParser->parseName(stream);
	if (name == "GRESKA") {
		errorFlag = true;
		return;
	}

	std::string opt = argsParser->parseOpt(stream);
	if (opt == "GRESKA") {
		errorFlag = true;
		return;
	}

	std::string inputString = "";

	// CTRL Z to end multi line input
	if (!inputTaken) inputString = argsParser->parseMultiLineInput(stream, inputTaken);
	if (inputString == "GRESKA") {
		errorFlag = true;
		return;
	}
	//if (inputTaken) return nullptr;

	if (!inputTaken) inputString = argsParser->parseArguments(stream, inputTaken);
	if (inputString == "GRESKA") {
		errorFlag = true;
		return;
	}
	//if (inputTaken) return nullptr;

	stream >> std::ws;
	std::string outputStreamName = "";
	bool outputApp = false;
	outputStreamName = argsParser->parseOutputRedirection(stream, outputApp);

	if (!inputTaken) inputString = argsParser->parseInputRedirection(stream, inputTaken);
	if (inputString == "GRESKA") {
		errorFlag = true;
		return;
	}

	if (!inputTaken) {
		std::cout << "Jos uvek nema input" << std::endl;
		errorFlag = true;
		return;
	}

	if (!stream.eof()) {
		std::cout << "Greska! Nekorektan unos!" << std::endl;
		errorFlag = true;
		return;
	}

	if (inputString != "") {
		std::cout << "Ulazni string je: " << inputString << std::endl;
	}

	if (outputStreamName != "") {
		std::cout << "Output stream je: " << outputStreamName << std::endl;
		if (outputApp == true) {
			std::cout << "Prosledjen dupli output operator." << std::endl;
		}
	}

	//outputName = outputStreamName;

	return;
}

ConsoleReader* CommandParser::getConsoleReader() {
	return this->consoleReader;
}