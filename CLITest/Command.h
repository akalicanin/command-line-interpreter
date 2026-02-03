#ifndef _COMMAND_H
#define _COMMAND_H

#include "Stream.h"
#include <iostream>

class Command {
protected:
	std::shared_ptr<InputStream> inputStream;
	std::shared_ptr<OutputStream> outputStream;

	Command(std::shared_ptr<InputStream> iStream, std::shared_ptr<OutputStream> oStream) 
	: inputStream(iStream), outputStream(oStream) {}
public:
	~Command() {}

	// Apstraktna metoda za koriscenje u izvedenim klasama komandi.
	// Koristi se radi pokretanja izvrsavanja komande.
	virtual void execute() = 0;
};


#endif