#include "TruncateParser.h"

#include <iostream>

CommandData* TruncateParser::parse(std::string& input, bool skipInput, bool skipOutput) {

    std::stringstream stream(input);
    CommandData* parsedData = new CommandData();
    std::string cmdName = "";
    cmdName = parseName(stream);
    parsedData->name = cmdName;

    std::string fileName = "";
    parsedData->hasFileArgument = true;
    bool inputIsTaken = false;
    bool checkError = false;

    if (skipInput) {
        inputIsTaken = true;
        parsedData->partOfPipeline = true;
    }

    if (!inputIsTaken) {
        fileName = parseFilenameArg(stream, inputIsTaken, checkError);
        if (inputIsTaken) {
            parsedData->inputFileName = fileName;
        }
        else {
            std::cerr << "Error! File reading unsuccessful!" << std::endl;
            return nullptr;
        }
    }

    stream >> std::ws;
    std::string errorMsg = "";
    if (errorChecker->checkStreamForAdditionalArguments(stream, errorMsg)) {
        std::cerr << errorMsg;
        return nullptr;
    }

    return parsedData;
}