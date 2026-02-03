#ifndef _COMMAND_DATA_STRUCT_H
#define _COMMAND_DATA_STRUCT_H

#include <string>
#include <vector>
#include <memory>

#include "Stream.h"

// Struktura koja sadrzi sve bitne informacije o komandi.
struct CommandData {
	std::string name = "";
	std::string opt = "";
	// Ako komanda treba da sadrzi string ulazni argument, on je arguments[0]. Sve dodatno ide nakon toga.
	std::vector<std::string> arguments = {};
	std::string inputFileName = "";
	std::string outputFileName = "";

	bool hasFileArgument = false;
	bool outputAppend = false;

	// Samo za pipeline
	bool partOfPipeline = false;
	std::shared_ptr<InputStream> inputStream = nullptr;
	std::shared_ptr<OutputStream> outputStream = nullptr;
};

#endif
