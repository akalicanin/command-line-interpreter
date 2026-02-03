#ifndef _PIPE_PARSER_H
#define _PIPE_PARSER_H

#include <vector>
#include <string>

class PipeParser {
public:
	std::vector<std::string>* parse(std::string* input, std::vector<int> positions);

};

#endif