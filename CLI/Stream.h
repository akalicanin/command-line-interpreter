#ifndef _STREAM_H
#define _STREAM_H

#include <sstream>

class InputStream {
protected:
	InputStream() {};
public:

	// Apstraktna komanda za citanje ulaznog toka komande.
	virtual std::stringstream* read() = 0;
};

class OutputStream {
protected:
	OutputStream() {};
public:
	
	// Apstraktna klasa za pisanje na izlazni tok komande.
	virtual void write(std::stringstream& output) = 0;
};

#endif

