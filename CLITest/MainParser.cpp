#include "MainParser.h"

#include <iostream>

CommandData* MainParser::parse(std::string& input, bool skipInput, bool skipOutput) {

    CommandData* parsedData = nullptr;

    std::stringstream stream(input);

    std::string commandName = parseName(stream);
    if (commandName == "") return nullptr;

    std::string errorMsg = "";
    if (errorChecker->checkLineForSpecialChars(commandName, errorMsg)) {
        std::cerr << errorMsg;
        return nullptr;
    }

    if (parseMap.find(commandName) != parseMap.end()) {
        parsedData = parseMap[commandName]->parse(input, skipInput, skipOutput);
    }
    else {
        std::cerr << "Error! Unknown command: " << commandName << std::endl;
        return nullptr;
    }

    return parsedData;
}
