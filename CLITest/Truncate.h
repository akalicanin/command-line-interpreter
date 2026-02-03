#ifndef _TRUNCATE_H
#define _TRUNCATE_H

#include "Command.h"

class Truncate : public Command {

public:
	Truncate(std::shared_ptr<InputStream> iStream, std::shared_ptr<OutputStream> oStream)
		: Command(iStream, oStream) {}

	virtual void execute() override;
};

#endif