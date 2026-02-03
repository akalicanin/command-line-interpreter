#include "FileStream.h"

std::stringstream* FileInputStream::read() {
	FileReader* fileReader = new FileReader();
	if (fileReader->openFile(fileName)) {
		std::string* temp = fileReader->read();
		if (!temp) {
			delete(fileReader);
			return nullptr;
		}
		std::stringstream* stream = new std::stringstream(*temp);
		delete(fileReader);
		return stream;
	}
	else {
		delete(fileReader);
		return nullptr;
	}
}

void FileOutputStream::write(std::stringstream& output) {
	FileWriter* fileWriter = new FileWriter();
	if (fileWriter->openFile(fileName, append)) {
		fileWriter->write(output);
		delete(fileWriter);
		return;
	}
	else {
		delete(fileWriter);
		return;
	}
}