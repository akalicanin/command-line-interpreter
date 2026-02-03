#include "TimeDateParser.h"

#include <iostream>

CommandData* TimeDateParser::parse(std::string& input, bool skipInput, bool skipOutput) {

    std::stringstream stream(input);
    CommandData* parsedData = new CommandData();
    std::string cmdName = "";
    cmdName = parseName(stream);
    parsedData->name = cmdName;

    stream >> std::ws;
    bool checkError = false;
    
    if (!skipOutput) {
        bool outputAppend = false;
        std::string outputStreamName = parseOutputRedirection(stream, outputAppend, checkError);

        parsedData->outputFileName = outputStreamName;
        parsedData->outputAppend = outputAppend;

    }

    stream >> std::ws;
    std::string errorMsg = "";
    if (errorChecker->checkStreamForAdditionalArguments(stream, errorMsg)) {
        std::cerr << errorMsg;
        return nullptr;
    }

    return parsedData;
}
