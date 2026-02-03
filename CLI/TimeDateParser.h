#ifndef _TIME_DATE_PARSER_H
#define _TIME_DATE_PARSER_H

#include "Parser.h"

class TimeDateParser : public Parser {
public:
	virtual CommandData* parse(std::string& input, bool skipInput, bool skipOutput);
};

#endif