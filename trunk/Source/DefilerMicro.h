#pragma once

#include <BWAPI.h>
#include "HighCommand.h"
class HighCommand;

class DefilerMicro
{
public:
	DefilerMicro();
	DefilerMicro(HighCommand* h);
	void micro(BWAPI::Unit* unit);
private:
	HighCommand* hc;
};