#ifndef _TRUNCATE_PARSER_H
#define _TRUNCATE_PARSER_H

#include "Parser.h"

class TruncateParser : public Parser {
public:

	virtual CommandData* parse(std::string& input, bool skipInput, bool skipOutput);

};

#endif