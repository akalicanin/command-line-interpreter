#ifndef _RM_PARSER_H
#define _RM_PARSER_H

#include "Parser.h"

class RmParser : public Parser {
public:

	virtual CommandData* parse(std::string& input, bool skipInput, bool skipOutput);

};

#endif