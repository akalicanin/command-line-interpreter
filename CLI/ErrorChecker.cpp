#include "ErrorChecker.h"

#include <iostream>
#include <vector>

void ErrorChecker::formPositionalErrorMsg(std::string& errorMsg, int originalLineLength, std::vector<int> errorPositions) {
	std::string arrows(originalLineLength, ' ');
	for (int i = 0; i < errorPositions.size(); i++) {
		arrows[errorPositions[i]] = '^';
	}
	errorMsg.append(arrows);
	errorMsg.append("\n");
}
