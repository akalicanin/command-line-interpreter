#include "EchoParser.h"

#include <iostream>

CommandData* EchoParser::parse(std::string& input, bool skipInput, bool skipOutput) {

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
        inputString = parseMultiLineInput(stream, inputIsTaken, checkError);
        if (inputIsTaken) {
            parsedData->arguments.push_back(inputString);
        }
    }

    if (!inputIsTaken && !checkError) {
        inputString = parseStringArg(stream, inputIsTaken, checkError);
        if (inputIsTaken) {
            parsedData->arguments.push_back(inputString);
        }
    }
    
    if (!inputIsTaken && !checkError) {
        inputString = parseFilenameArg(stream, inputIsTaken, checkError);
        if (inputIsTaken) {
            parsedData->inputFileName = inputString;
            parsedData->hasFileArgument = true;
        }
    }

    if (!inputIsTaken && !checkError) {
        inputString = parseInputRedirection(stream, inputIsTaken, checkError);
        if (inputIsTaken) {
            parsedData->inputFileName = inputString;
            parsedData->hasFileArgument = true;
        }
    }
   
    if (checkError) {
        return nullptr;
    }

    if (!skipOutput) {
        std::string output = "";
        bool outputAppend = false;
        output = parseOutputRedirection(stream, outputAppend, checkError);
        if (checkError) {
            return nullptr;
        }
        parsedData->outputAppend = outputAppend;
        parsedData->outputFileName = output;
    }

    if (!inputIsTaken) {
        inputString = parseInputRedirection(stream, inputIsTaken, checkError);
        if (checkError) {
            return nullptr;
        }
        else {
            parsedData->inputFileName = inputString;
            parsedData->hasFileArgument = true;
        }
    }

    stream >> std::ws;
    std::string errorMsg = "";
    if (errorChecker->checkStreamForAdditionalArguments(stream, errorMsg)) {
        std::cerr << errorMsg;
        return nullptr;
    }

    if (!inputIsTaken) {
        std::cerr << "Error! Missing input argument!" << std::endl;
        return nullptr;
    }
    
    return parsedData;
}
