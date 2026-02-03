#ifndef _ECHO_H
#define _ECHO_H

#include "Command.h"

class Echo : public Command {

public:
	Echo(std::shared_ptr<InputStream> iStream, std::shared_ptr<OutputStream> oStream)
		: Command(iStream, oStream) {}

	virtual void execute() override;
};

#endif