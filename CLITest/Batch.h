#ifndef _BATCH_H
#define _BATCH_H

#include "Command.h"

class Batch : public Command {

public:
	Batch(std::shared_ptr<InputStream> iStream, std::shared_ptr<OutputStream> oStream)
		: Command(iStream, oStream) {}

	virtual void execute() override;
};

#endif