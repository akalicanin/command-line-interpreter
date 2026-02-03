#include "Head.h"

void Head::execute() {

	std::stringstream* input = this->inputStream->read();
	if (input == nullptr) {
		return;
	}
	std::stringstream output;

	std::string digits = this->opt.substr(2);
	
	int count = -1;
	try {
		count = std::stoi(digits);
	}
	catch (std::invalid_argument const& ex)
	{
		std::cout << "Error!" << ex.what() << '\n';
		delete input;
		return;
	}

	std::string line;
	bool firstline = true;
	while (count != 0 && std::getline(*input, line) ) {
		if (!firstline) output << std::endl;
		output << line;
		firstline = false;
		count--;
	}

	this->outputStream->write(output);

	delete input;
}
