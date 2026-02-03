#include "CommandBuilder.h"

#include "ConsoleStream.h"
#include "StringStream.h"
#include "FileStream.h"

std::shared_ptr<Command> CommandBuilder::build(CommandData* parsedData) {
	std::shared_ptr<Command> cmd = nullptr;
	
	std::string name;
	name = parsedData->name;
	if (buildsMap.find(name) != buildsMap.end()) {
		cmd = buildsMap[name](parsedData);
	}
	else {
		return nullptr;
	}

	return cmd;
}

std::shared_ptr<Echo> CommandBuilder::buildEcho(CommandData* parsedData) {

	std::shared_ptr<InputStream> input;
	std::shared_ptr<OutputStream> output;

	input = parsedData->inputStream;
	output = parsedData->outputStream;

	if (!input) {
		if (parsedData->hasFileArgument) {
			input = std::make_shared<FileInputStream>(parsedData->inputFileName);
		}
		else {
			input = std::make_shared<StringInputStream>(parsedData->arguments[0]);
		}
	}
	if (!output) {
		if (parsedData->outputFileName == "cout") {
			output = std::make_shared<ConsoleOutputStream>();
		}
		else {
			output = std::make_shared<FileOutputStream>(parsedData->outputFileName, parsedData->outputAppend);
		}
	}

	std::shared_ptr<Echo> command = std::make_shared<Echo>(input, output);

	return command;
}

std::shared_ptr<TimeCmd> CommandBuilder::buildTime(CommandData* parsedData) {

	std::shared_ptr<OutputStream> output;

	output = parsedData->outputStream;

	if (!output) {
		if (parsedData->outputFileName == "cout") {
			output = std::make_shared<ConsoleOutputStream>();
		}
		else {
			output = std::make_shared<FileOutputStream>(parsedData->outputFileName, parsedData->outputAppend);
		}
	}
	
	std::shared_ptr<TimeCmd> command = std::make_shared<TimeCmd>(nullptr, output);

	return command; 
}

std::shared_ptr<DateCmd> CommandBuilder::buildDate(CommandData* parsedData) {
	std::shared_ptr<OutputStream> output;

	output = parsedData->outputStream;

	if (!output) {
		if (parsedData->outputFileName == "cout") {
			output = std::make_shared<ConsoleOutputStream>();
		}
		else {
			output = std::make_shared<FileOutputStream>(parsedData->outputFileName, parsedData->outputAppend);
		}
	}

	std::shared_ptr<DateCmd> command = std::make_shared<DateCmd>(nullptr, output);

	return command;
}

std::shared_ptr<Touch> CommandBuilder::buildTouch(CommandData* parsedData) {
	std::shared_ptr<InputStream> input;
	std::shared_ptr<OutputStream> output;

	input = parsedData->inputStream;
	output = parsedData->outputStream;

	if (!input) {
		input = std::make_shared<StringInputStream>(parsedData->inputFileName);
	}
	if (!output) {
		output = std::make_shared<ConsoleOutputStream>();
	}

	std::shared_ptr<Touch> command = std::make_shared<Touch>(input, output);

	return command;
}

std::shared_ptr<Wc> CommandBuilder::buildWc(CommandData* parsedData) {
	std::shared_ptr<InputStream> input;
	std::shared_ptr<OutputStream> output;

	input = parsedData->inputStream;
	output = parsedData->outputStream;

	if (!input) {

		if (parsedData->hasFileArgument) {
			input = std::make_shared<FileInputStream>(parsedData->inputFileName);
		}
		else {
			input = std::make_shared<StringInputStream>(parsedData->arguments[0]);
		}
	}
	if (!output) {
		if (parsedData->outputFileName == "cout") {
			output = std::make_shared<ConsoleOutputStream>();
		}
		else {
			output = std::make_shared<FileOutputStream>(parsedData->outputFileName, parsedData->outputAppend);
		}
	}

	std::shared_ptr<Wc> command = std::make_shared<Wc>(input, output, parsedData->opt);

	return command;
}

std::shared_ptr<Prompt> CommandBuilder::buildPrompt(CommandData* parsedData) {
	std::shared_ptr<InputStream> input;

	input = parsedData->inputStream;


	if (!input) {
		if (parsedData->hasFileArgument) {
			input = std::make_shared<FileInputStream>(parsedData->inputFileName);
		}
		else {
			input = std::make_shared<StringInputStream>(parsedData->arguments[0]);
		}
	}
	
	std::shared_ptr<Prompt> command = std::make_shared<Prompt>(input, nullptr);

	return command;
}

std::shared_ptr<Truncate> CommandBuilder::buildTruncate(CommandData* parsedData) {
	std::shared_ptr<InputStream> input;

	input = parsedData->inputStream;

	if (!input) {
		input = std::make_shared<StringInputStream>(parsedData->inputFileName);
	}

	std::shared_ptr<Truncate> command = std::make_shared<Truncate>(input, nullptr);

	return command;
}

std::shared_ptr<Rm> CommandBuilder::buildRm(CommandData* parsedData) {
	std::shared_ptr<InputStream> input;

	input = parsedData->inputStream;

	if (!input) {
		input = std::make_shared<StringInputStream>(parsedData->inputFileName);
	}

	std::shared_ptr<Rm> command = std::make_shared<Rm>(input, nullptr);

	return command;
}

std::shared_ptr<Head> CommandBuilder::buildHead(CommandData* parsedData) {
	std::shared_ptr<InputStream> input;
	std::shared_ptr<OutputStream> output;

	input = parsedData->inputStream;
	output = parsedData->outputStream;

	if (!input) {
		if (parsedData->hasFileArgument) {
			input = std::make_shared<FileInputStream>(parsedData->inputFileName);
		}
		else {
			input = std::make_shared<StringInputStream>(parsedData->arguments[0]);
		}
	}
	if (!output) {
		if (parsedData->outputFileName == "cout") {
			output = std::make_shared<ConsoleOutputStream>();
		}
		else {
			output = std::make_shared<FileOutputStream>(parsedData->outputFileName, parsedData->outputAppend);
		}
	}

	std::shared_ptr<Head> command = std::make_shared<Head>(input, output, parsedData->opt);

	return command;

}

std::shared_ptr<Tr> CommandBuilder::buildTr(CommandData* parsedData) {
	std::shared_ptr<InputStream> input;
	std::shared_ptr<OutputStream> output;

	input = parsedData->inputStream;
	output = parsedData->outputStream;

	if (!input) {
		if (parsedData->hasFileArgument) {
			input = std::make_shared<FileInputStream>(parsedData->inputFileName);
		}
		else {
			input = std::make_shared<StringInputStream>(parsedData->arguments[0]);
		}
	}
	if (!output) {
		if (parsedData->outputFileName == "cout") {
			output = std::make_shared<ConsoleOutputStream>();
		}
		else {
			output = std::make_shared<FileOutputStream>(parsedData->outputFileName, parsedData->outputAppend);
		}
	}
	
	std::string what = "";
	std::string with = "";
	if (parsedData->hasFileArgument || parsedData->partOfPipeline) {
		what = parsedData->arguments[0];
		if (parsedData->arguments.size() == 2) {
			with = parsedData->arguments[1];
		}
	}
	else {
		what = parsedData->arguments[1];
		if (parsedData->arguments.size() == 3) {
			with = parsedData->arguments[2];
		}
	}

	std::shared_ptr<Tr> command = std::make_shared<Tr>(input, output, what, with);

	return command;

}

std::shared_ptr<Batch> CommandBuilder::buildBatch(CommandData* parsedData) {
	std::shared_ptr<InputStream> input;
	std::shared_ptr<OutputStream> output;

	input = parsedData->inputStream;
	output = parsedData->outputStream;

	if (!input) {
		if (parsedData->hasFileArgument) {
			input = std::make_shared<FileInputStream>(parsedData->inputFileName);
		}
		else {
			input = std::make_shared<StringInputStream>(parsedData->arguments[0]);
		}
	}
	if (!output) {
		if (parsedData->outputFileName == "cout") {
			output = std::make_shared<ConsoleOutputStream>();
		}
		else {
			output = std::make_shared<FileOutputStream>(parsedData->outputFileName, parsedData->outputAppend);
		}
	}

	std::shared_ptr<Batch> command = std::make_shared<Batch>(input, output);

	return command;
}
