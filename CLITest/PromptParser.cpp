#include "PromptParser.h"
#include <iostream>

CommandData* PromptParser::parse(std::string& input, bool skipInput, bool skipOutput) {
    std::stringstream stream(input);
    CommandData* parsedData = new CommandData();
    std::string cmdName = "";
    cmdName = parseName(stream);
    parsedData->name = cmdName;

    std::string inputString = "";
    stream >> std::ws;
    bool inputIsTaken = false;
    bool checkError = false;

    if (skipInput) {
        inputIsTaken = true;
        parsedData->partOfPipeline = true;
    }

    if (!inputIsTaken) {
        inputString = parseStringArg(stream, inputIsTaken, checkError);
        if (inputIsTaken) {
            parsedData->arguments.push_back(inputString);
        }
    }

    //if (!inputIsTaken && !checkError) {
    //    inputString = parseFilenameArg(stream, inputIsTaken, checkError);
    //    if (inputIsTaken) {
    //        parsedData->inputFileName = inputString;
    //        parsedData->hasFileArgument = true;
    //    }
    //}

    if (checkError) {
        return nullptr;
    }


    if (!inputIsTaken) {
        std::cerr << "Error! Missing input argument!" << std::endl;
        return nullptr;
    }
   
    stream >> std::ws;
    std::string errorMsg = "";
    if (errorChecker->checkStreamForAdditionalArguments(stream, errorMsg)) {
        std::cerr << errorMsg;
        return nullptr;
    }

    return parsedData;
}