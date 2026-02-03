#include "PipeParser.h"

std::vector<std::string>* PipeParser::parse(std::string* input, std::vector<int> positions) {
    std::vector<std::string>* list = new std::vector<std::string>();

    int startingPosition = 0;
    int pipePosition = 0;

    std::string commandLine;

    for (int i = 0; i < positions.size(); i++) {
        pipePosition = positions[i];

        commandLine = input->substr(startingPosition, static_cast<std::basic_string<char, std::char_traits<char>, std::allocator<char>>::size_type>(pipePosition) - startingPosition);
        list->push_back(commandLine);

        startingPosition = pipePosition + 1;
    }

    commandLine = input->substr(startingPosition);
    list->push_back(commandLine);

    return list;
}
