#ifndef _COMMAND_BUILDER_H
#define _COMMAND_BUILDER_H

#include "CommandsList.h"
#include "CommandData.h"

#include <memory>
#include <unordered_map>
#include <functional>

class CommandBuilder {
private:

	std::unordered_map<std::string, std::function<std::shared_ptr<Command>(CommandData* parsedData)>> buildsMap;

public:

	CommandBuilder()
	{
		buildsMap["echo"] = [this](CommandData* parsedData) { return buildEcho(parsedData); };
		buildsMap["time"] = [this](CommandData* parsedData) { return buildTime(parsedData); };
		buildsMap["date"] = [this](CommandData* parsedData) { return buildDate(parsedData); };
		buildsMap["touch"] = [this](CommandData* parsedData) { return buildTouch(parsedData); };
		buildsMap["wc"] = [this](CommandData* parsedData) { return buildWc(parsedData); };
		buildsMap["prompt"] = [this](CommandData* parsedData) { return buildPrompt(parsedData); };
		buildsMap["truncate"] = [this](CommandData* parsedData) { return buildTruncate(parsedData); };
		buildsMap["rm"] = [this](CommandData* parsedData) { return buildRm(parsedData); };
		buildsMap["head"] = [this](CommandData* parsedData) { return buildHead(parsedData); };
		buildsMap["tr"] = [this](CommandData* parsedData) { return buildTr(parsedData); };
		buildsMap["batch"] = [this](CommandData* parsedData) { return buildBatch(parsedData); };
	};

	std::shared_ptr<Command> build(CommandData* parsedData);
	std::shared_ptr<Echo> buildEcho(CommandData* parsedData);
	std::shared_ptr<TimeCmd> buildTime(CommandData* parsedData);
	std::shared_ptr<DateCmd> buildDate(CommandData* parsedData);
	std::shared_ptr<Touch> buildTouch(CommandData* parsedData);
	std::shared_ptr<Wc> buildWc(CommandData* parsedData);
	std::shared_ptr<Prompt> buildPrompt(CommandData* parsedData);
	std::shared_ptr<Truncate> buildTruncate(CommandData* parsedData);
	std::shared_ptr<Rm> buildRm(CommandData* parsedData);
	std::shared_ptr<Head> buildHead(CommandData* parsedData);
	std::shared_ptr<Tr> buildTr(CommandData* parsedData);
	std::shared_ptr<Batch> buildBatch(CommandData* parsedData);

};
#endif

