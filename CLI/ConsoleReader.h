#ifndef _CONSOLE_READER_H
#define _CONSOLE_READER_H

#include "Reader.h"

class ConsoleReader : public Reader {
public:
	ConsoleReader() : Reader() {};
	~ConsoleReader() {};

	// Cita unos iz konzole i vraca kao string.
	// Vrsi proveru o duzini ulaznog stringa i skracuje po potrebi.
	virtual std::string* read() override;
};

#endif