#include "FileWriter.h"

void FileWriter::write(std::stringstream& output) {
	if (file.is_open()) {
		file << output.rdbuf();
		file.close();
	}
	else {
		std::cerr << "Error! Attempted writing to a file that isn't open!" << std::endl;
	}
}

bool FileWriter::openFile(std::string fileName, bool append) {
	closeFile();
	if (append) {
		file.open(fileName, std::ios::app);
		if (file.is_open()) {
			return true;
		}
		else {
			return false;
		}
	}
	else {
		file.open(fileName, std::ios::out);
		if (file.is_open()) {
			return true;
		}
		else {
			return false;
		}
	}
}

void FileWriter::closeFile() {
	if (file.is_open()) {
		file.close();
	}
}

bool FileWriter::doesFileExist(std::string fileName) {
	closeFile();
	// jedini mod otvaranja koji ne pravi nov fajl je 'in'.
	file.open(fileName, std::ios::in);
	if (file.is_open()) {
		return true;
	}
	else {
		return false;
	}
	closeFile();
}
