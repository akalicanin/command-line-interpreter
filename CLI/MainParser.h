#ifndef _MAIN_PARSER_H
#define _MAIN_PARSER_H

#include "Parser.h"
#include "EchoParser.h"
#include "TimeDateParser.h"
#include "TouchParser.h"
#include "WcParser.h"
#include "PromptParser.h"
#include "TruncateParser.h"
#include "RmParser.h"
#include "HeadParser.h"
#include "TrParser.h"
#include "BatchParser.h"

#include <unordered_map>
//#include <functional>

class MainParser : public Parser {
private:
	std::unordered_map<std::string, std::shared_ptr<Parser>> parseMap;
public:
	MainParser() : Parser() 
	{
		parseMap["echo"] = std::make_shared<EchoParser>();
		parseMap["time"] = std::make_shared<TimeDateParser>();
		parseMap["date"] = std::make_shared<TimeDateParser>();
		parseMap["touch"] = std::make_shared<TouchParser>();
		parseMap["wc"] = std::make_shared<WcParser>();
		parseMap["prompt"] = std::make_shared<PromptParser>();
		parseMap["truncate"] = std::make_shared<TruncateParser>();
		parseMap["rm"] = std::make_shared<RmParser>();
		parseMap["head"] = std::make_shared<HeadParser>();
		parseMap["tr"] = std::make_shared<TrParser>();
		parseMap["batch"] = std::make_shared<BatchParser>();
	};

	virtual CommandData* parse(std::string& input, bool skipInput, bool skipOutput);
};

#endif

