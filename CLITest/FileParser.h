#ifndef _FILE_PARSER_H
#define _FILE_PARSER_H

#include <memory>
#include <sstream>

#include "Parser.h"
#include "Reader.h"

class FileParser : public Parser {
private:
	FileReader* fileReader;

	std::string fileName;

	std::string fileContents;

public:
	FileParser(FileReader* FR)
		: fileReader(FR), fileName(""), fileContents(""), Parser() {};

	virtual void Parse() override;

	std::string getFileName();
	std::string getFileContents();
	FileReader* getFileReader();

	void setFileName(std::string fileName);

};


#endif
