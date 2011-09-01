#pragma once
#include <BWAPI.h>
#include "HighCommand.h"
class HighCommand;

#include "EnemyUnitData.h"
#include <boost/unordered_map.hpp>
#include "Task.h"

using namespace BWAPI;

typedef boost::unordered_map<Unit*, EnemyUnitData> EnemyUnitMap ;

/**
 * The EnemyUnitDataManager maintains additional data about enemy units, such as their last known position.
 */
class EnemyUnitDataManager
{
public:
	EnemyUnitDataManager(HighCommand* h);
	void update();
	void onStart();
	void onUnitDiscover(Unit* u);
	void onUnitEvade(Unit* u);
	void onUnitShow(Unit* u);
	void onUnitHide(Unit* u);
	void onUnitCreate(Unit* u);
	void onUnitDestroy(Unit* u);
	void onUnitMorph(Unit* u);
	void onUnitRenegade(Unit* u);

	/**
	 * For every enemy unit, a CombatTask is created with the unit as target.
	 */
	void createTask(TaskType tasktype, Position position, Unit* u);
	std::list<Task> getTasklist(TaskType tasktype);

	/**
	 * Find the enemy unit closest to the given unit that can attack air units.
	 */
	BWAPI::Unit* nearestEnemyThatCanAttackAir(BWAPI::Unit* unit);

	/**
	 * Count the number of known enemy units of type unittype.
	 */
	int count(BWAPI::UnitType unittype);

	/**
	 * Return the entire collection of enemy units and data.
	 */
	EnemyUnitMap getMap();

	/**
	 * Return only the collection of known flying enemy units.
	 */
	EnemyUnitMap mapIsFlyer(EnemyUnitMap map);

	std::string chat();
private:
	HighCommand* hc;
	void updateUnit(Unit* u);
	void cleanup();
	void clearTasklists();

	EnemyUnitMap unitmap;
	std::list<Task> scouttasklist;
	std::list<Task> combattasklist;
};