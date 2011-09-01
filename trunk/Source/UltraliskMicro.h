#pragma once

#include <BWAPI.h>
#include "HighCommand.h"
class HighCommand;

class UltraliskMicro
{
public:
	UltraliskMicro();
	UltraliskMicro(HighCommand* h);
	void micro(BWAPI::Unit* unit);
private:
	HighCommand* hc;
};