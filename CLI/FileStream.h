#ifndef _FILE_STREAMS_H
#define _FILE_STREAMS_H

#include "Stream.h"

#include "FileReader.h"
#include "FileWriter.h"

class FileInputStream : public InputStream {
private:
	std::string fileName;
public:
	FileInputStream(std::string fileName) : fileName(fileName), InputStream() {}

	// Cita ceo sadrzaj fajla.
	virtual std::stringstream* read();

};

class FileOutputStream : public OutputStream {
private:
	std::string fileName;
	bool append = false;
public:
	FileOutputStream(std::string fileName, bool append) : fileName(fileName), append(append), OutputStream() {}

	// Upisuje prosledjeni output argument u output fajl koji je prosledjen
	// prilikom kreiranja FileOutputStreama.
	virtual void write(std::stringstream& output);

};

#endif

