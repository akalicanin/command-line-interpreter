#ifndef _RM_H
#define _RM_H

#include "Command.h"

class Rm : public Command {

public:
	Rm(std::shared_ptr<InputStream> iStream, std::shared_ptr<OutputStream> oStream)
		: Command(iStream, oStream) {}

	virtual void execute() override;
};

#endif
