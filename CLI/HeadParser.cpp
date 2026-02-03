#include "HeadParser.h"

#include <iostream>

CommandData* HeadParser::parse(std::string& input, bool skipInput, bool skipOutput) {
    std::stringstream stream(input);
    CommandData* parsedData = new CommandData();
    std::string cmdName = "";
    cmdName = parseName(stream);
    parsedData->name = cmdName;

    std::string optName = "";
    optName = parseOpt(stream);
    if (optName.length() > 7) {
        std::cerr << "Error! Head command line count number can be at most 5 digits!" << std::endl;
        return nullptr;
    }
    else if (optName.length() < 3) {
        std::cerr << "Error! Head optional argument is incorrect!" << std::endl;
        return nullptr;
    }
    else if (optName.substr(0, 2) != "-n") {
        std::cerr << "Error! Head optional argment is incorrect!" << std::endl;
    }
    if (optName == "") {
        std::cerr << "Error! Missing opt argument!" << std::endl;
        return nullptr;
    }
    parsedData->opt = optName;

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
