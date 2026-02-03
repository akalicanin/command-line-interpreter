#ifndef _TR_PARSER_H
#define _TR_PARSER_H

#include "Parser.h"

class TrParser : public Parser {
public:

	virtual CommandData* parse(std::string& input, bool skipInput, bool skipOutput);

};

#endif

