#ifndef _ECHO_PARSER_H
#define _ECHO_PARSER_H

#include "Parser.h"

class EchoParser : public Parser {
public:

	virtual CommandData* parse(std::string& input, bool skipInput, bool skipOutput);

};

#endif

