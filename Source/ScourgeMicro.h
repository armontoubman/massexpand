#pragma once

#include <BWAPI.h>
#include "HighCommand.h"
class HighCommand;

class ScourgeMicro
{
public:
	ScourgeMicro();
	ScourgeMicro(HighCommand* h);
	void micro(BWAPI::Unit* unit);
private:
	HighCommand* hc;
};