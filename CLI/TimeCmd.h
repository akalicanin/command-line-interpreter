#ifndef _TIME_CMD_H
#define _TIME_CMD_H

#include "Command.h"

class TimeCmd : public Command {
public:
	TimeCmd(std::shared_ptr<InputStream> iStream, std::shared_ptr<OutputStream> oStream)
		: Command(iStream, oStream) {};

	virtual void execute() override;
};

#endif