#include "DateCmd.h"

#include <chrono>
#include <ctime>
#include <iomanip>

void DateCmd::execute() {
	std::stringstream input;
	std::time_t sysTime = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
	std::tm localTime;
	localtime_s(&localTime, &sysTime);

	input << std::put_time(&localTime, "%d.%m.%Y");

	outputStream->write(input);
}
