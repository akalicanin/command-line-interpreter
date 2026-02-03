#ifndef _ERROR_CHECKER_H
#define _ERROR_CHECKER_H

#include <string>
#include <vector>
#include <sstream>

class ErrorChecker {
private:
	const std::string invalidFileChars = R"(<>:"\?*)";
	const std::string invalidChars = R"(:\?*%!+@#$^&)"; // ne sadrzi | / " <>
	const std::string invalidCharsForCmdNameAndOpt = R"(!@#$%^&*()_+|}{":?><`~-/\';[])";

	// u regularnoj liniji, ne smem da gledam:
	// | - pipeline
	// >< - i/o redirekcija
	// " - string argument (parno)
	// - <- opcioni argument
	// / <- naredni folder u nazivu file-a
public:
	ErrorChecker() {}
	~ErrorChecker() {}

	void formPositionalErrorMsg(std::string& errorMsg, int originalLineLength, std::vector<int> errorPositions);

	// true ako ima greska, false ako nema greske
	bool checkFileArgForForbiddenChars(std::string fileName, std::string& errorMsg) {
		int position = 0;
		std::vector<int> errorPositions;

		for (std::string::iterator it = fileName.begin(); it != fileName.end(); it++, position++) {
			if (invalidFileChars.find(*it) != std::string::npos) {
				errorPositions.push_back(position);
			}
		}

		if (errorPositions.size() != 0) {
			errorMsg = "Error! Forbidden characters found in filename:\n";
			errorMsg.append(fileName);
			errorMsg.append("\n");
			formPositionalErrorMsg(errorMsg, static_cast<int>(fileName.size()), errorPositions);
			return true;
		}
		else {
			return false;
		}
	}

	bool checkStreamForAdditionalArguments(std::stringstream& stream, std::string& errorMsg) {
		if (!stream.eof()) {
			// sve ovde je deo greske.
			std::string stringFromStream = stream.str();

			int position = static_cast<int>(stream.tellg());
			if (position < 0) position = 0;
			int streamSize = static_cast<int>(stringFromStream.size());

			std::string spaces(position, ' ');
			std::string arrows(streamSize - position, '^');

			errorMsg = "Error! Unnecessary additional arguments found:\n";
			errorMsg.append(stringFromStream);
			errorMsg.append("\n");
			errorMsg.append(spaces);
			errorMsg.append(arrows);
			errorMsg.append("\n");

			return true;
		}
		else {
			return false;
		}
	}

	bool checkLineForSpecialChars(std::string line, std::string& errorMsg) {
		int position = 0;
		std::vector<int> errorPositions;

		for (std::string::iterator it = line.begin(); it != line.end(); it++, position++) {
			if (invalidCharsForCmdNameAndOpt.find(*it) != std::string::npos) {
				errorPositions.push_back(position);
			}
		}

		if (errorPositions.size() != 0) {
			errorMsg = "Error! Forbidden characters found in command:\n";
			errorMsg.append(line);
			errorMsg.append("\n");
			formPositionalErrorMsg(errorMsg, static_cast<int>(line.size()), errorPositions);
			return true;
		}
		else {
			return false;
		}
	}

	bool checkStringArgumentForInvalidChars(std::stringstream& stream, std::string stringArg, std::string& errorMsg) {
		// ovo vrsi proveru odmah nakon uzimanja inputString argumenta
		if (stream.peek() != ' ' && !stream.eof()) {
			int position = static_cast<int>(stream.tellg());
			if (position < 0) position = 0;
			std::vector<int> errorPositions;
			std::string stringFromStream = stream.str();

			while (stream.peek() != ' ' && !stream.eof()) {
				errorPositions.push_back(position);
				position++;
				stream.get();
			}

			errorMsg = "Error! Forbidden characters found after string argument:\n";
			errorMsg.append(stringFromStream);
			errorMsg.append("\n");
			formPositionalErrorMsg(errorMsg, static_cast<int>(stream.str().size()), errorPositions);
			return true;
		}
		else {
			return false;
		}
	}
};
#endif

