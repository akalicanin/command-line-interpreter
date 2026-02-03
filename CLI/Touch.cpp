#include "Touch.h"

#include "FileReader.h"
#include "FileWriter.h"

void Touch::execute() {
	
	FileWriter* fileWriter = new FileWriter();

	std::stringstream* input = inputStream->read();
	if (input == nullptr) {
		return;
	}
	std::string fileName = input->str();

	if (fileWriter->doesFileExist(fileName)) {
		std::cerr << "Error! File with name " << fileName << " already exists!" << std::endl;
	}
	else {
		fileWriter->openFile(fileName, false);
	}

	delete(fileWriter);
	delete(input);

}
