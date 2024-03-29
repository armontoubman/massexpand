#pragma once
#include <BWAPI.h>
#include "HighCommand.h"
class HighCommand;

#include "EigenUnitData.h"
#include <boost/unordered_map.hpp>

using namespace BWAPI;

typedef boost::unordered_map<Unit*, EigenUnitData> EigenUnitMap ;

/**
 * The EigenUnitDataManager maintains additional data about our own units, such as when they were seen by enemies.
 */
class EigenUnitDataManager
{
public:
	EigenUnitDataManager(HighCommand* h);
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
	 * Query if one of our units has been seen by the enemy.
	 */
	bool unitIsSeen(Unit* u);

	std::string chat();
private:
	HighCommand* hc;
	void updateUnit(Unit* u);

	EigenUnitMap unitmap;
};