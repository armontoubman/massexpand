#pragma once
#include <BWAPI.h>
#include "UnitGroup.h"

class HighCommand;

class DefilerMicro;
class DroneMicro;
class HydraliskMicro;
class LurkerMicro;
class OverlordMicro;
class ScourgeMicro;
class UltraliskMicro;
class ZerglingMicro;

using namespace BWAPI;

/**
 * The MicroManager coordinates the microing of all our mobile units.
 */
class MicroManager
{
public:
	MicroManager(HighCommand* h);
	void update();
	/**
	 * Check if the unit has already been microed this frame.
	 */
	bool isUnitMicrod(BWAPI::Unit* unit);
	/**
	 * Note that the unit has been microed this frame.
	 */
	void unitIsMicrod(BWAPI::Unit* unit);
private:
	HighCommand* hc;

	/**
	 * Group of units that has been microed (reset each frame).
	 */
	UnitGroup microdUnits;

	DefilerMicro* defilerMicro;
	DroneMicro* droneMicro;
	HydraliskMicro* hydraliskMicro;
	LurkerMicro* lurkerMicro;
	OverlordMicro* overlordMicro;
	ScourgeMicro* scourgeMicro;
	UltraliskMicro* ultraliskMicro;
	ZerglingMicro* zerglingMicro;

	/**
	 * Find the right micro class for the unit and process it.
	 */
	void selectMicro(BWAPI::Unit* unit);
};