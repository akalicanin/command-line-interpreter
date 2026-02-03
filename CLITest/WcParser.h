#ifndef _WC_PARSER_H
#define _WC_PARSER_H

#include "Parser.h"

class WcParser : public Parser {
public:

	virtual CommandData* parse(std::string& input, bool skipInput, bool skipOutput);

};

#endif