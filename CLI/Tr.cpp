#include "Tr.h"

void Tr::execute() {
	std::stringstream* input = this->inputStream->read();
	std::string inputString = input->str();
	
	size_t position = 0;

	while ((position = inputString.find(this->what, position)) != std::string::npos) {
		inputString.replace(position, this->what.length(), this->with);
		position += static_cast<size_t>(this->with.length());
	}

	std::stringstream output;
	output << inputString;
	this->outputStream->write(output);

	delete input;
}
