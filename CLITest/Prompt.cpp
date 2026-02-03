#include "Prompt.h"
#include "Engine.h"

void Prompt::execute() {

	std::stringstream* input = this->inputStream->read();
	std::string newPrompt = input->str();

	Engine* engine = Engine::getInstance();
	engine->setPrompt(newPrompt);
	
	delete input;
}