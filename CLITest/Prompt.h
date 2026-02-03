#ifndef _PROMPT_H
#define _PROMPT_H

#include "Command.h"

class Prompt : public Command {
public:
	Prompt(std::shared_ptr<InputStream> iStream, std::shared_ptr<OutputStream> oStream)
		: Command(iStream, oStream) {};

	virtual void execute() override;
};

#endif
