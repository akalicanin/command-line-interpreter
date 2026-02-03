#include "PipeChecker.h"

#include <vector>

bool PipeChecker::check(std::string* input, std::vector<int>& positions) {
	int leftCount = 0;
	int rightCount = 0;
	int pos = 0;
	bool hasString = false;

	if (input->find('"') == std::string::npos) {
		hasString = false;
	}
	else {
		hasString = true;
	}

	// pozicije svih | koji odvajaju pipeline
	positions = {};
	
	std::string *line = input;

	for (auto it = line->begin(); it != line->end(); it++) {
		if (*it == '|') {
			leftCount = 0;
			rightCount = 0;
			if (hasString) {
				for (auto it1 = line->begin(); it1 != it; it1++) {
					if (*it1 == '"') {
						leftCount++;
					}
				}
				for (auto it2 = line->end() - 1; it2 != it; it2--) {
					if (*it2 == '"') {
						rightCount++;
					}
				}
			}
			if (rightCount % 2 == 0 && leftCount % 2 == 0) {
				positions.push_back(pos);
			}
		}

		pos++;
	}

	if (positions.empty()) {
		return false;
	}
	else {
		return true;
	}
}
