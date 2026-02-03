#ifndef _DATE_CMD_H
#define _DATE_CMD_H

#include "Command.h"

class DateCmd : public Command {
public:
	DateCmd(std::shared_ptr<InputStream> iStream, std::shared_ptr<OutputStream> oStream)
		: Command(iStream, oStream) {};

	virtual void execute() override;
};

#endif