#include "TrParser.h"

#include <iostream>

CommandData* TrParser::parse(std::string& input, bool skipInput, bool skipOutput) {

    std::stringstream stream(input);
    CommandData* parsedData = new CommandData();
    std::string cmdName = "";
    cmdName = parseName(stream);
    parsedData->name = cmdName;

    // tr [argument] [what] [with]
    //    ^any type  ^string ^string
    // novo:
    // () <- optional
    // [] <- required
    // tr (argument) [what] (with)
    // ako nema argument, u pitanju je multiline input

    std::string inputString = "";
    std::string whatString = "";
    std::string withString = "";
    bool inputIsTaken = false;
    bool whatIsTaken = false;
    bool withIsTaken = false;
    bool checkError = false;
    bool multiLineSituation = false;
    // input == 1: situacija tr [what].
    // argument je multilien input, with je ""
    // tr [argument] pa da nema what spada u ovu situaciju ali ta greska je ovde samo nemoguca da se dogodi
    // 
    // input == 2: tr [argument] [what]
    // with je ""
    // ali kako razlikovati tr [what] [with] a argument je multiline input od ovoga???
    // 
    // input == 3: tr [argument] [what] [with nema multiline input
    //

    stream >> std::ws;

    if (skipInput) {
        inputIsTaken = true;
        parsedData->partOfPipeline = true;
    }

    if (!inputIsTaken && !checkError) {
        inputString = parseStringArg(stream, inputIsTaken, checkError);
        if (inputIsTaken) {
            // Ako je postojao samo jedan argument. to je "with" a input argument dolazi iz multiline-a
            // obradjivanje slucaja jednog argumenta (multiline tr slucaj)
            // Znaci ovde smo uzeli samo with. Pokusacemo da uzmemo output redirekciju, ako je uspesno, to je kraj.
            stream >> std::ws;
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
            if (stream.eof()) {
                multiLineSituation = true;
                inputIsTaken = false;
                whatString = inputString;
                inputString = "";
                inputString = parseMultiLineInput(stream, inputIsTaken, checkError);
                if (inputIsTaken) {
                    parsedData->arguments.push_back(inputString);
                    parsedData->arguments.push_back(whatString);
                    withString = "";
                    parsedData->arguments.push_back(withString);
                    
                    return parsedData;
                }
                else {
                    std::cerr << "Error! Missing arguments for Tr command." << std::endl;
                    return nullptr;
                }
            }
            else {
                parsedData->arguments.push_back(inputString);
            }
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

    // Uzimanje what i with
    whatString = parseStringArg(stream, whatIsTaken, checkError);
    if (whatIsTaken) {
        parsedData->arguments.push_back(whatString);
    }
    else {
        std::cerr << "Error! Couldn't parse 'what' argument!" << std::endl;
        return nullptr;
    }

    if (stream && stream.peek() == '"') {
        stream.get();
        std::getline(stream, withString, '"');
        if (stream.eof()) {
            std::cout << "Error! With argument string is incomplete!" << std::endl;
            return nullptr;
        }
        stream.get();
        withIsTaken = true;
        parsedData->arguments.push_back(withString);
    }

    if (!withIsTaken) {
        withString = "";
        parsedData->arguments.push_back(withString);
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
        std::cerr << "Error! Input argument missing for command: " << cmdName << '!' << std::endl;
        return nullptr;
    }

    return parsedData;
}
