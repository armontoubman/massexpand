#pragma once
#include <BWAPI.h>

using namespace BWAPI;

/**
 * EigenUnitData holds extra data about our own units that is not provided by the game.
 * \see EigenUnitDataManager
 */
class EigenUnitData
{
public:
	EigenUnitData();

	int hitPoints;
	bool seenByEnemy;
	int seenByEnemyTime;
	Position seenByEnemyPosition;
};