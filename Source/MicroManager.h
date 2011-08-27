#pragma once
#include <BWAPI.h>
#include "UnitGroup.h"

class HighCommand;

class DefilerMicro;
class DroneMicro;
class HydraliskMicro;
class LurkerMicro;
class OverlordMicro;
class UltraliskMicro;
class ZerglingMicro;

using namespace BWAPI;

class MicroManager
{
public:
	MicroManager(HighCommand* h);
	void update();
	bool isUnitMicrod(BWAPI::Unit* unit);
	void unitIsMicrod(BWAPI::Unit* unit);
private:
	HighCommand* hc;

	UnitGroup microdUnits;

	DefilerMicro* defilerMicro;
	DroneMicro* droneMicro;
	HydraliskMicro* hydraliskMicro;
	LurkerMicro* lurkerMicro;
	OverlordMicro* overlordMicro;
	UltraliskMicro* ultraliskMicro;
	ZerglingMicro* zerglingMicro;

	void selectMicro(BWAPI::Unit* unit);
};