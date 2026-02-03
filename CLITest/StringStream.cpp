#include "StringStream.h"

std::stringstream* StringInputStream::read() {
	std::stringstream* stream = new std::stringstream(input);
	return stream;
}

void StringOutputStream::write(std::stringstream& output) {
	*this->outputStream << output.rdbuf();
}

void StringOutputStream::clearOutputStream() {
	this->outputStream->str("");
}

std::stringstream* StringOutputStream::getOutputStreamData() {
	return this->outputStream;
}
