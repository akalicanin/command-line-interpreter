#ifndef _FILE_WRITER_H
#define _FILE_WRITER_H

#include <iostream>
#include <fstream>
#include <sstream>

class FileWriter {
private:
	std::ofstream file;
public:
	FileWriter() {};
	~FileWriter() {
		closeFile();
	}
	
	// Prima string tok kao argument koji potom upisuje u fajl.
	// Nacin upisivanja zavisi od prosledjenog 'append' argumenta u metodi openFile.
	void write(std::stringstream& output);

	// Otvara fajl. Vraca true za uspesno, false za neuspesno otvaranje.
	// Ako je 'append' true, u metodi write() ce samo dodati prosledjeni string tok na kraj fajla.
	bool openFile(std::string fileName, bool append);

	// Zatvara trenutni fajl ako je otvoren.
	void closeFile();

	// Vraca true ako file postoji, false ako ne. Otvara i zatvara file.
	bool doesFileExist(std::string fileName);
};

#endif