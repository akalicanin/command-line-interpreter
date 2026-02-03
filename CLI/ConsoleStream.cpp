#include "ConsoleStream.h"

#include <iostream>

void ConsoleOutputStream::write(std::stringstream& output) {
	std::cout << output.rdbuf() << std::endl;
}
