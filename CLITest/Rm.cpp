#include "Rm.h"

#include <cstdio>

void Rm::execute() {
	std::stringstream* input = inputStream->read();
	if (input == nullptr) {
		return;
	}
	std::string fileName = input->str();

	const char* charFileName = fileName.c_str();

	if (remove(charFileName)) {
		std::cerr << "Error! File deletion failed!" << std::endl;
	}

	delete input;
}