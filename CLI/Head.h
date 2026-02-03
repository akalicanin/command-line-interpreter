#ifndef _HEAD_H
#define _HEAD_H

#include "Command.h"

class Head : public Command {
private:
	std::string opt;
public:
	Head(std::shared_ptr<InputStream> iStream, std::shared_ptr<OutputStream> oStream, std::string& opt)
		: Command(iStream, oStream), opt(opt) {}

	virtual void execute() override;
};

#endif