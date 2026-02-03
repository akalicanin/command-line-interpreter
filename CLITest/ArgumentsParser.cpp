#include "ArgumentsParser.h"

#include <memory>
#include <sstream>
#include <iostream>


void ArgumentsParser::Parse() {
}

std::string ArgumentsParser::parseName(std::istringstream& stream) {
	std::string name;
	stream >> std::ws;
	stream >> name;
	if (commandNames.find(name) == commandNames.end()) {
		std::cout << "Greska, neprepoznat naziv komande: " << name << std::endl;
		return "GRESKA";
	}
	// Ovo verovatno nije potrebno:
	// Kad god upises naziv i ukucas komandu,
	// Uvek moze da se ocekuje multi-line input,
	// a ne samo da nisi uneo dovoljno argumenata.
	/*if (!stream && name != "end") {
		std::cout << "Nedovoljno argumenata." << std::endl;
		return "GRESKA";
	}*/
	std::cout << "IME: " << name << std::endl;
	return name;
}

std::string ArgumentsParser::parseOpt(std::istringstream& stream) {
	stream >> std::ws;
	std::string opt = "";
	if (stream && stream.peek() == '-') {
		stream >> opt;
		if (commandOpts.find(opt) == commandOpts.end()) {
			std::cout << "Greska, nepoznat naziv opt-a: " << opt << std::endl;
			return "GRESKA";
		}
	}
	if (opt != "") {
		std::cout << "OPT: " << opt << std::endl;
	}
	stream >> std::ws;
	return opt;
}

std::string ArgumentsParser::parseMultiLineInput(std::istringstream& stream, bool& inputTaken) {
	std::string ulazniString = "";
	if (stream.eof()) {
		std::cout << "EOF slucaj!" << std::endl;
		char ch;
		while (ch = std::cin.get()) {
			if (ch == EOF) {
				break;
			}
			ulazniString += ch;
		}
		std::cin.clear(); // Cistim cinput da ne pravim dalje probleme
		if (ulazniString == "") {
			std::cout << "U EOF slucaju, nema ulaznog stringa." << std::endl;
			return "GRESKA";
		}
		ulazniString = ulazniString.substr(0, ulazniString.length() - 1); // Skidam poslednji '/n'
		std::cout << "Ulazni string je: " << '\n' << ulazniString << std::endl;
		inputTaken = true;
	}
	return ulazniString;
}

std::string ArgumentsParser::parseArguments(std::istringstream& stream, bool& inputTaken) {
	std::string inputArgument = "";
	stream >> std::ws;
	inputArgument = parseStringArg(stream, inputTaken);
	if (!inputTaken && inputArgument != "GRESKA") {
		inputArgument = parseFilenameArg(stream, inputTaken);
	}
	if (!inputTaken && inputArgument != "GRESKA") {
		inputArgument = parseInputRedirection(stream, inputTaken);
	}
	return inputArgument;
}

std::string ArgumentsParser::parseStringArg(std::istringstream& stream, bool& inputTaken) {
	stream >> std::ws;
	std::string inputString = "";
	if (stream && stream.peek() == '"') {
		stream.get();
		std::getline(stream, inputString, '"');
		if (stream.eof()) {
			std::cout << "Greska, nije kompletan string!" << std::endl;
			return "GRESKA";
		}
		inputTaken = true;
	}
	return inputString;
}

std::string ArgumentsParser::parseFilenameArg(std::istringstream& stream, bool& inputTaken) {
	std::string fileName = "";
	std::string fileText = "";
	stream >> std::ws;
	if (stream && (stream.peek() != '<') && (stream.peek() != '>')) {
		stream >> fileName;
		inputTaken = true;
		if (fileName == "") {
			std::cout << "Greska, nema input argumenta." << std::endl;
			return "GRESKA";
		}
		getFileParser()->setFileName(fileName);
		getFileParser()->Parse();
		fileText = getFileParser()->getFileContents();
	}
	return fileText;
}

std::string ArgumentsParser::parseInputRedirection(std::istringstream& stream, bool& inputTaken) {
	stream >> std::ws;
	std::string inputStreamName = "";
	std::string fileContents = "";
	if (stream && stream.peek() == '<') {
		if (inputTaken) {
			std::cout << "Vec je uzet input!" << std::endl;
			return "GRESKA";
		}
		stream.get();
		stream >> std::ws;
		stream >> inputStreamName;
		if (inputStreamName == "") {
			std::cout << "Greska, nema input argumenta." << std::endl;
			return "GRESKA";
		}
		getFileParser()->setFileName(inputStreamName);
		getFileParser()->Parse();
		fileContents = getFileParser()->getFileContents();
		inputTaken = true;
	}
	return fileContents;
}

std::string ArgumentsParser::parseOutputRedirection(std::istringstream& stream, bool& outputAppend) {
	stream >> std::ws;
	std::string outputStreamName = "";
	outputAppend = false;
	if (stream && stream.peek() == '>') {
		stream.get();
		if (stream.peek() == '>') {
			stream.get();
			outputAppend = true;

		}
		stream >> std::ws;
		stream >> outputStreamName;
		if (outputStreamName == "") {
			std::cout << "Greska, nema output argumenta." << std::endl;
			return "GRESKA";
		}
	}
	return outputStreamName;
}

FileParser* ArgumentsParser::getFileParser() {
	return this->fileParser;
}
