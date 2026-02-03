#ifndef _CONSOLE_STREAM_H
#define _CONSOLE_STREAM_H

#include "Stream.h"

class ConsoleOutputStream : public OutputStream {
public:
	ConsoleOutputStream() : OutputStream() {};

	// Ispisuje output komande na konzoli.
	virtual void write(std::stringstream& output);
};

#endif