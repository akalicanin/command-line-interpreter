#include "Engine.h"

#include <iostream>

#include "Stream.h"
#include "StringStream.h"

Engine* Engine::getInstance() {
	static Engine engine;
	return &engine;
}

void Engine::setRunningState(bool state) {
	this->isRunning = state;
}

bool Engine::getRunningState() {
	return this->isRunning;
}

std::string Engine::getPrompt() {
	return this->prompt;
}

void Engine::setPrompt(std::string newprompt) {
	this->prompt = newprompt;
}

void Engine::simulatePipeline(std::string* input, std::vector<int>& positions) {
	std::vector<std::string>* listOfInputs = nullptr;
	listOfInputs = pipeParser->parse(input, positions);

	std::shared_ptr<StringOutputStream> oStream = std::make_shared<StringOutputStream>();

	for (int i = 0; i < listOfInputs->size(); i++) {
		std::string line = (*listOfInputs)[i];

		bool skipInput = true;
		bool skipOutput = true;

		i == 0 ? skipInput = false : skipInput = true;
		i == listOfInputs->size() - 1 ? skipOutput = false : skipOutput = true;

		CommandData* parseData;
		parseData = mainParser->parse(line, skipInput, skipOutput);
		if (parseData == nullptr) {
			return;
		}

		if (i != listOfInputs->size() - 1) {
			parseData->outputStream = oStream;
		}
		if (i != 0) {
			std::string outputData;
			outputData = oStream->getOutputStreamData()->str();
			parseData->inputStream = std::make_shared<StringInputStream>(outputData);
			oStream->clearOutputStream();
		}

		std::shared_ptr<Command> cmd = nullptr;
		cmd = commandBuilder->build(parseData);
		if (cmd == nullptr) {
			//std::cerr << "Error! Command not formed successfully!" << std::endl;
			return;
		}

		cmd->execute();

	}
}

void Engine::simulateLine(std::string* cmdline) {

	std::string* line;

	if (cmdline) {
		line = cmdline;
	}
	else {
		line = consoleReader->read();
		if (line == nullptr) {
			//std::cerr << "Error! Input line invalid!" << std::endl;
			return;
		}
	}

	if (line->find('|') != std::string::npos) {
		std::vector<int> positions = {};
		if (pipeChecker->check(line, positions)) {
			simulatePipeline(line, positions);
			return;
		}
	}

	CommandData* parseData;
	parseData = mainParser->parse(*line, false, false);
	if (parseData == nullptr) {
		//std::cerr << "Error! Command data not formed successfully!";
		return;
	}

	std::shared_ptr<Command> cmd = nullptr;
	cmd = commandBuilder->build(parseData);
	if (cmd == nullptr) {
		//std::cerr << "Error! Command not formed successfully!" << std::endl;
		return;
	}

	cmd->execute();

	return;
}

void Engine::simulate() {
	while (isRunning) {
		std::cout << prompt + " ";
		simulateLine(nullptr);
	}
}
