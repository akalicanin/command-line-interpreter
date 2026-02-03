#include "ConsoleReader.h"

#include <iostream>

std::string* ConsoleReader::read() {
    std::string* line = new std::string;
    std::getline(std::cin, *line);
    *line = line->substr(0, 512);
    return line;
}
