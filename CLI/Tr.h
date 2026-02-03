#ifndef _TR_H
#define _TR_H

#include "Command.h"

class Tr : public Command {
private:
	std::string what;
	std::string with;
public:
	Tr(std::shared_ptr<InputStream> iStream, std::shared_ptr<OutputStream> oStream,
		std::string& what, std::string& with)
		: Command(iStream, oStream), what(what), with(with) {}

	virtual void execute() override;
};

#endif