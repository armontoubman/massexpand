#pragma once
#include <BWAPI.h>
#include "HighCommand.h"
class HighCommand;

#include "UnitGroup.h"

using namespace BWAPI;

/**
 * The EigenUnitGroupManager divides our units into UnitGroups and maintains these groups.
 */
class EigenUnitGroupManager
{
public:
	EigenUnitGroupManager(HighCommand* h);
	void update();

	/**
	 * Our starting units are put into groups as soon as we can access them fully.
	 */
	void init();
	void onUnitCreate(Unit* u);
	void onUnitDestroy(Unit* u);
	void onUnitMorph(Unit* u);
	void onUnitRenegade(Unit* u);

	/**
	 * Get the set with all UnitGroups.
	 */
	std::set<UnitGroup*> getUnitGroupSet();
	std::string chat();

	/**
	 * Check if a UnitGroup pointer is pointing to the seperate Drone group.
	 */
	bool groupIsDroneUG(UnitGroup* ug);

	/**
	 * Get the pointer to the group that unit u is in.
	 */
	UnitGroup* getGroupOfUnit(BWAPI::Unit* u);

	/**
	 * Get a pointer to the Drone group.
	 */
	UnitGroup* getDroneUG();

private:
	HighCommand* hc;
	std::set<UnitGroup*> unitgroupset;

	/**
	 * Drones are kept seperate in a group with a fixed pointer.
	 */
	UnitGroup* droneUG;
	bool initiated;

	/**
	 * Only units that are ours, not buildings, not Larva and not Eggs are put into groups.
	 */
	bool isGroupable(Unit* u);

	/**
	 * Removes unit u from the group it is in.
	 */
	void removeUnit(Unit* u);
	void cleanup();

	/**
	 * Give Overlords to groups of Mutalisks, disband groups that are too small and split up groups that are too big.
	 */
	void balanceGroups();

	/**
	 * Drops Drones in the Drone group, gives Overlords new groups and drops other units into a fitting group.
	 */
	void assignUnit(Unit* u);
	UnitGroup* findFittingGroupForUnit(Unit* u);
	void moveUnitBetweenGroups(Unit* u, UnitGroup* ug1, UnitGroup* ug2);

	/**
	 * Splits a UnitGroup into two new UnitGroups.
	 */
	void splitGroup(UnitGroup* ugptr);
	bool unitIsInAGroup(Unit* u);
};