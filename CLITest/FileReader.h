#ifndef _FILE_READER_H
#define _FILE_READER_H

#include "Reader.h"

class FileReader : public Reader {
private:
	std::ifstream file;
public:

	FileReader() : Reader() {};

	~FileReader() {
		closeFile();
	}

	// Cita ceo sadrzaj fajla i vraca kao string.
	virtual std::string* read() override;

	// Cita tacno jednu liniju iz fajla.
	virtual std::string* readLine();

	// Otvara fajl. Vraca true za uspesno, false za neuspesno otvaranje.
	bool openFile(std::string fileName);
	
	// Zatvara trenutni fajl ako je otvoren.
	void closeFile();

};

#endif
