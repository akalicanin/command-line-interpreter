#include "Wc.h"

void Wc::execute() {

	int count = 0;
	std::stringstream* input = inputStream->read();
	if (input == nullptr) {
		return;
	}

	if (opt == "-w") { // Citanje broja slova.
		std::string str;
		while (*input >> str) {
			count++;
		}
	}
	else if (opt == "-c") { // Citanje broja karaktera.
		char ch;
		while (input->get(ch)) {
			count++;
		}
	}

	std::stringstream output;
	output << count;
	outputStream->write(output);

	delete input;
}
