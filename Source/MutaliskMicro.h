#pragma once

#include <BWAPI.h>
#include "HighCommand.h"
class HighCommand;

class MutaliskMicro
{
public:
	MutaliskMicro();
	MutaliskMicro(HighCommand* h);
	void micro(BWAPI::Unit* unit);
private:
	HighCommand* hc;
};