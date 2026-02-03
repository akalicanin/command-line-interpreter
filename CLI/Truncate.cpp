#include "Truncate.h"

#include "FileReader.h"
#include "FileWriter.h"

void Truncate::execute() {
	FileWriter* fileWriter = new FileWriter();

	std::stringstream* input = inputStream->read();
	if (input == nullptr) {
		return;
	}
	std::string fileName = input->str();

	if (fileWriter->doesFileExist(fileName)) {
		fileWriter->openFile(fileName, false);
		fileWriter->closeFile();
	}
	else {
		std::cerr << "Error! File with name " << fileName << " doesn't exist." << '\n';
	}

	delete(fileWriter);
	delete(input);
}