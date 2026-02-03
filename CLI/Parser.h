#ifndef _PARSER_H
#define _PARSER_H

#include "CommandData.h"
#include "ErrorChecker.h"

#include <string>
#include <sstream>

class Parser {
protected:

	std::unique_ptr<ErrorChecker> errorChecker;

	Parser() {
		errorChecker = std::make_unique<ErrorChecker>();
	};
	~Parser() {}

public:

	// Apstraktna metoda parse, za koriscenje u izvedenim klasama.
	// Vraca pokazivac na strukturu koja nosi sve bitne informacije za komandu.
	virtual CommandData* parse(std::string& input, bool skipInput, bool skipOutput) = 0;

	// Parsira ime iz ulaznog toka.
	virtual std::string parseName(std::stringstream& stream);

	// Parsira opcioni argument iz ulaznog toka.
	virtual std::string parseOpt(std::stringstream& stream);

	// Parsira viselinijski input iz ulaznog toka (CTRL+Z)
	virtual std::string parseMultiLineInput(std::stringstream& stream, bool& inputTaken, bool& errorCheck);

	// Parsira input okruzen navodnicima iz ulaznog toka.
	virtual std::string parseStringArg(std::stringstream& stream, bool& inputTaken, bool& errorCheck);

	// Parsira input koji predstavlja naziv fajla iz ulaznog toka.
	virtual std::string parseFilenameArg(std::stringstream& stream, bool& inputTaken, bool& errorCheck);

	// Parsira redirekciju inputa iz ulaznog toka.
	virtual std::string parseInputRedirection(std::stringstream& stream, bool& inputTaken, bool& errorCheck);

	// Parsira redirekciju outputa iz ulaznog toka.
	virtual std::string parseOutputRedirection(std::stringstream& stream, bool& outputAppend, bool& errorCheck);

};

#endif