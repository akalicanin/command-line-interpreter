#include "Echo.h"

void Echo::execute() {

	std::stringstream* input = inputStream->read();
	if (!input) {
		return;
	}

	outputStream->write(*input);
	delete input;
}
