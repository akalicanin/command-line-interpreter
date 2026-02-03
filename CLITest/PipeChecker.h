#ifndef _PIPE_CHECKER_H
#define _PIPE_CHECKER_H

#include <string>
#include <vector>

class PipeChecker {
public:
	// Returns true if input line are commands in a pipeline.
	bool check(std::string* input, std::vector<int>& positions);
};

#endif