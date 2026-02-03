#ifndef _TOUCH_PARSER_H
#define _TOUCH_PARSER_H

#include "Parser.h"

class TouchParser : public Parser {
public:
	
	virtual CommandData* parse(std::string& input, bool skipInput, bool skipOutput);

};

#endif