#include "Parser.h"

#include <memory>
#include <iostream>
#include <conio.h>


std::string Parser::parseName(std::stringstream& stream) {
	std::string name = "";
	stream >> std::ws;
	stream >> name;
	return name;
}

std::string Parser::parseOpt(std::stringstream& stream) {
	std::string opt = "";
	stream >> std::ws;
	stream >> opt;
	return opt;
}

std::string Parser::parseMultiLineInput(std::stringstream& stream, bool& inputTaken, bool& errorCheck) {
	std::string input = "";
	stream >> std::ws;
	if (stream.eof()) {
		char ch;
		while (true) {
			if (_kbhit()) {
				ch = _getch();
				if (ch == 26) {
					std::cout << '\n';
					break;
				}
				if (ch == '\r') {
					std::cout << '\n';
					input += '\n';
				}
				else if (ch == '\b') {
					if (input.empty()) {
						continue;
					}
					std::cout << "\b \b";
					input.pop_back();
				}
				else {
					std::cout << ch;
					input += ch;
				}
			}
		}
		std::cin.clear();
		if (input == "") {
			std::cerr << "Error! Missing multi-line input!" << std::endl;
			errorCheck = true;
			return "";
		}
		inputTaken = true;
	}
	return input;
}

std::string Parser::parseStringArg(std::stringstream& stream, bool& inputTaken, bool& errorCheck) {
	stream >> std::ws;
	std::string inputString = "";
	std::string formattedString = "";

	if (stream && stream.peek() == '"') {
		stream.get();
		std::getline(stream, inputString, '"');
		if (stream.eof()) {
			std::cout << "Error! String argument incomplete!" << std::endl;
			errorCheck = true;
			return "";
		}
		std::string errorMsg = "";
		if (errorChecker->checkStringArgumentForInvalidChars(stream, inputString, errorMsg)) {
			std::cerr << errorMsg;
			errorCheck = true;
			return "";
		}
		//if (stream.peek() != ' ' && !stream.eof()) {
		//	std::cerr << "Error! Unexpected characters at the end of string argument!" << std::endl;
		//	inputTaken = false;
		//	errorCheck = true;
		//	return "";
		//}
		inputTaken = true;
	}
	else if (stream.eof()) {
		//std::cerr << "Error! Missing input string argument!" << std::endl;
		// nepotreban poziv greske
		//errorCheck = true;
		// 
		return "";
	}
	stream >> std::ws;
	
	// Formatiranje '\n' u zapravo znak za novi red
	for (auto it = inputString.begin(); it != inputString.end(); it++) {
		if (*it == 92 && it != inputString.end() - 1) { // 92 asci = \ 
			if (*(it + 1) == 'n') { // '\n' 
				it++;
				formattedString += '\n';
				continue;
			}
		}
		formattedString += *it;
	}

	return formattedString;
}

std::string Parser::parseFilenameArg(std::stringstream& stream, bool& inputTaken, bool& errorCheck) {
	stream >> std::ws;
	const std::string invalidChars = R"(<>"\|?*)"; // ovde je '/' izdvojen zbog direktorijuma, a : zbog C:// npr
	std::string fileName = "";

	if (stream && (stream.peek() != '<') && (stream.peek() != '>')) {
		stream >> fileName;
		if (fileName == "") {
			std::cerr << "Error! File input argument missing!" << std::endl;
			errorCheck = true;
			return "";
		}
		inputTaken = true;
	}
	//if (fileName.find_first_of(invalidChars) != std::string::npos) {
	//	std::cerr << "Error! Forbidden characters in file name!" << std::endl;
	//	errorCheck = true;
	//	return "";
	//}

	std::string errorMsg = "";
	if (errorChecker->checkFileArgForForbiddenChars(fileName, errorMsg)) {
		std::cerr << errorMsg;
		errorCheck = true;
		return "";
	}
	

	return fileName;
}

std::string Parser::parseInputRedirection(std::stringstream& stream, bool& inputTaken, bool& errorCheck) {
	stream >> std::ws;
	const std::string invalidChars = R"(<>:"/\|?*)";
	std::string fileName = "";

	if (stream && stream.peek() == '<') {
		stream.get();
		stream >> std::ws;
		stream >> fileName;
		if (fileName == "") {
			std::cerr << "Error! Input redirection argument missing!" << std::endl;
			errorCheck = true;
			return "";
		}
		inputTaken = true;
	}

	//if (fileName.find_first_of(invalidChars) != std::string::npos) {
	//	std::cerr << "Error! Forbidden characters in file name!" << std::endl;
	//	errorCheck = true;
	//	return "";
	//}

	std::string errorMsg = "";
	if (errorChecker->checkFileArgForForbiddenChars(fileName, errorMsg)) {
		std::cerr << errorMsg;
		errorCheck = true;
		return "";
	}

	return fileName;
}

std::string Parser::parseOutputRedirection(std::stringstream& stream, bool& outputAppend, bool& errorCheck) {
	stream >> std::ws;
	std::string outputStreamName = "cout";
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
			std::cerr << "Error! Output redirection argument missing!" << std::endl;
			outputAppend = false;
			errorCheck = true;
			return "";
		}
	}

	std::string errorMsg = "";
	if (errorChecker->checkFileArgForForbiddenChars(outputStreamName, errorMsg)) {
		std::cerr << errorMsg;
		errorCheck = true;
		return "";
	}

	return outputStreamName;
}
