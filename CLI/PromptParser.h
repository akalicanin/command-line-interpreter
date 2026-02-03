#ifndef _PROMPT_PARSER_H
#define _PROMPT_PARSER_H

#include "Parser.h"

class PromptParser : public Parser {
public:

	virtual CommandData* parse(std::string& input, bool skipInput, bool skipOutput);

};

#endif