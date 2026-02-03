#ifndef _READER_H
#define _READER_H

#include <istream>
#include <fstream>
#include <string>

class Reader {
protected:
	Reader() {};
public:
	// Apstraktna metoda za citanje.
	virtual std::string* read() = 0;
};

#endif

