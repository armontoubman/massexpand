#pragma once
#include <BWAPI.h>

using namespace BWAPI;

/**
 * EnemyUnitData holds extra data about enemy units that is not provided by the game.
 * \see EnemyUnitDataManager
 */
class EnemyUnitData
{
public:
	EnemyUnitData();
	void update(Unit* u);

	UnitType unitType;
	int hitPoints;
	Position position;
	Position lastKnownPosition;
	int lastSeen;
};