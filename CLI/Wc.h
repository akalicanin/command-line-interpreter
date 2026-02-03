#ifndef _WC_H
#define _WC_H

#include "Command.h"

class Wc : public Command {
private:
	std::string opt;
public:
	Wc(std::shared_ptr<InputStream> iStream, std::shared_ptr<OutputStream> oStream, std::string& opt)
		: Command(iStream, oStream), opt(opt) {}

	virtual void execute() override;
};

#endif