#ifndef _TOUCH_H
#define _TOUCH_H

#include "Command.h"

class Touch : public Command {
public:
	Touch(std::shared_ptr<InputStream> iStream, std::shared_ptr<OutputStream> oStream)
		: Command(iStream, oStream) {}

	virtual void execute() override;
};

#endif