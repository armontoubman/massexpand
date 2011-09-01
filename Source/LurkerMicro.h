#pragma once

#include <BWAPI.h>
#include "HighCommand.h"
class HighCommand;

class LurkerMicro
{
public:
	LurkerMicro();
	LurkerMicro(HighCommand* h);
	void micro(BWAPI::Unit* unit);
private:
	HighCommand* hc;
	void hold(BWAPI::Unit* unit);
};