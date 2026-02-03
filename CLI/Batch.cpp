#include "Batch.h"

#include "Engine.h"

void Batch::execute() {
	std::stringstream* input = this->inputStream->read();
	if (!input) {
		return;
	}

	std::string* commandLine = new std::string();

	Engine* engine = Engine::getInstance();
	
	while (std::getline(*input, *commandLine)) {
		engine->simulateLine(commandLine);
	}

	delete commandLine;
	delete input;
}
