#pragma once

#include <BWAPI.h>
#include "HighCommand.h"
class HighCommand;

class HydraliskMicro
{
public:
	HydraliskMicro();
	HydraliskMicro(HighCommand* h);
	void micro(BWAPI::Unit* unit);
private:
	HighCommand* hc;
};