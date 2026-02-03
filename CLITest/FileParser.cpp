#include "FileParser.h"

void FileParser::Parse() {
	FileReader* fileReader = this->getFileReader();
	fileReader->OpenFile(fileName);
	std::ostringstream* fileStream = fileReader->ReadFile();
	if (!fileStream) {
		fileContents = "GRESKA";
		return;
	}
	fileContents = fileStream->str();
}

std::string FileParser::getFileName() {
	return fileName;
}

std::string FileParser::getFileContents() {
	return fileContents;
}

FileReader* FileParser::getFileReader() {
	return this->fileReader;
}

void FileParser::setFileName(std::string fileName) {
	this->fileName = fileName;
}

