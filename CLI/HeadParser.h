#ifndef _HEAD_PARSER_H
#define _HEAD_PARSER_H

#include "Parser.h"

class HeadParser : public Parser {
public:

	virtual CommandData* parse(std::string& input, bool skipInput, bool skipOutput);

};

#endif

