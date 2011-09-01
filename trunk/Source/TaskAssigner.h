#pragma once
#include <BWAPI.h>
#include "HighCommand.h"

using namespace BWAPI;

/**
 * The TaskAssigner assigns Tasks to UnitGroups. The assignments are stored in a plan. Drones have a seperate plan.
 * \see EigenUnitGroupManager
 * \see Task
 */
class TaskAssigner
{
public:
	TaskAssigner(HighCommand* h);
	void update();
	std::map<UnitGroup*, Task> getPlan();
	std::map<BWAPI::Unit*, Task> getDronePlan();

	/**
	 * Find the Task that was assigned to the unit.
	 */
	Task getTaskOfUnit(BWAPI::Unit* unit);

	void onUnitDestroy(Unit* u);
	void onUnitMorph(Unit* u);

private:
	HighCommand* hc;

	std::map<UnitGroup*, Task> plan;
	std::map<BWAPI::Unit*, Task> dronePlan;
	void makePlan();
	void assign(UnitGroup* ug, Task task);
	void assignDrone(BWAPI::Unit*, Task task);
	
	/**
	 * Find the most fitting task for the UnitGroup, with the preferred TaskType
	 */
	Task bestTask(UnitGroup* ug, TaskType tasktype);
	bool taskIsAssigned(Task task);
	int countDronesOnTask(Task task);
	Task nearestTask(BWAPI::Position pos, std::list<Task> tasklist);
};