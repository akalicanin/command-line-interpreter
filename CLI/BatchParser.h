#ifndef _BATCH_PARSER_H
#define _BATCH_PARSER_H

#include "Parser.h"

class BatchParser : public Parser {
public:

	virtual CommandData* parse(std::string& input, bool skipInput, bool skipOutput);

};

#endif

