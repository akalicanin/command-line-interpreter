#ifndef _STRING_STREAMS_H
#define _STRING_STREAMS_H

#include "Stream.h"

class StringInputStream : public InputStream {
private:
	std::string input;
public:
	StringInputStream(std::string input) : input(input), InputStream() {}

	// Cita ceo prosledjeni input string za komandu.
	virtual std::stringstream* read();
};

class StringOutputStream : public OutputStream {
private:
	std::stringstream* outputStream;
public:
	StringOutputStream() : OutputStream() {
		outputStream = new std::stringstream();
	}

	// Pise ceo prosledjeni output stringstream za komandu.
	virtual void write(std::stringstream& output);

	void clearOutputStream();

	std::stringstream* getOutputStreamData();
};
#endif