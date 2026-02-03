#ifndef _ENGINE_H
#define _ENGINE_H

#include "ConsoleReader.h"
#include "CommandsList.h"
#include "CommandData.h"
#include "CommandBuilder.h"
#include "MainParser.h"

#include "PipeChecker.h"
#include "PipeParser.h"

#include "ErrorChecker.h"

class Engine {
private:

	std::string prompt;
	bool isRunning;

	std::unique_ptr<ConsoleReader> consoleReader;
	std::unique_ptr<MainParser> mainParser;
	std::unique_ptr<CommandBuilder> commandBuilder;

	std::unique_ptr<PipeChecker> pipeChecker;
	std::unique_ptr<PipeParser> pipeParser;

	std::unique_ptr<ErrorChecker> errorChecker;

	Engine() : isRunning(true), prompt(">") {
		consoleReader = std::make_unique<ConsoleReader>();
		mainParser = std::make_unique<MainParser>();
		commandBuilder = std::make_unique<CommandBuilder>();

		pipeChecker = std::make_unique<PipeChecker>();
		pipeParser = std::make_unique<PipeParser>();

		errorChecker = std::make_unique<ErrorChecker>();
	};
	~Engine() {};

public:

	// Singleton instance
	static Engine* getInstance();

	// Sets running state of Engine.
	void setRunningState(bool state);

	// Gets running state of Engine.
	bool getRunningState();

	// Gets the current prompt identifier for the console.
	std::string getPrompt();

	// Sets the prompt identifier for the console.
	void setPrompt(std::string newprompt);

	// Simulates multiple commands connected by a pipeline.
	void simulatePipeline(std::string* input, std::vector<int>& positions);

	// Simulates one line of the program, or a single command line passed in as argument.
	void simulateLine(std::string* cmdline);

	// Simulates the program until turned off by changing isRunning to false.
	void simulate();

};
#endif

