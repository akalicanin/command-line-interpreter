#include "FileReader.h"

#include <iostream>
#include <sstream>

std::string* FileReader::read() {
    if (file.is_open()) {
        std::string* fileContents = new std::string(std::istreambuf_iterator<char>(file), std::istreambuf_iterator<char>());
        if (*fileContents == "") {
            std::cout << "Error! Attempted reading an empty file." << std::endl;
            return nullptr;
        }
        return fileContents;
    }
    else {
        return nullptr;
    }
}

std::string* FileReader::readLine() {
    if (file.is_open()) {
        if (!file.eof()) {
            std::string* line = new std::string();
            std::getline(file, *line);
            return line;
        }
        else {
            return nullptr;
        }
    }
    else {
        return nullptr;
    }
}

bool FileReader::openFile(std::string fileName) {
    closeFile();

    file.open(fileName, std::ios::in);
    if (file.is_open()) {
        return true;
    }
    else {
        std::cout << "Error! File with name: " << fileName << " doesn't exist!\n";
        return false;
    }
}

void FileReader::closeFile() {
    if (file.is_open()) {
        file.close();
    }
}

