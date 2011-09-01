#pragma once

#include "UltraliskMicro.h"
#include <BWAPI.h>
#include "Task.h"
#include "GlobalMicro.h"
#include "Util.h"

UltraliskMicro::UltraliskMicro()
{
}

UltraliskMicro::UltraliskMicro(HighCommand* h)
{
	this->hc = h;
}

void UltraliskMicro::micro(BWAPI::Unit* unit)
{
	Task task = this->hc->ta->getTaskOfUnit(unit);

	if(unit->isIrradiated())
	{
		UnitGroup enemies = allEnemyUnits().inRadius(dist(30), unit->getPosition()).not(isFlyer);
		if(enemies.size() > 0)
		{
			unit->attack(getNearestUnit(unit->getPosition(), enemies)->getPosition());
		}
	}
	else
	{
		if(unit->isUnderStorm())
		{
			moveToNearestBase(unit);
		}
		else
		{
			UnitGroup swarms = allUnits()(Dark_Swarm).inRadius(dist(9), unit->getPosition());
			if(swarms.size() > 0)
			{
				if(isUnderDarkSwarm(unit))
				{
					// game AI
				}
				else
				{
					BWAPI::Unit* swarm = getNearestUnit(unit->getPosition(), swarms);
					if(swarm != NULL)
					{
						unit->move(swarm->getPosition());
					}
				}
			}
			else
			{
				if(task.getType() != ScoutTask && unit->getDistance(task.getPosition()) < dist(6) && BWAPI::Broodwar->isVisible(BWAPI::TilePosition(task.getPosition())))
				{
					UnitGroup enemies = allEnemyUnits().inRadius(dist(6), unit->getPosition());
					if(enemies.size() > 0)
					{
						unit->attack(*enemies.begin());
					}
					else
					{
						unit->attack(task.getPosition());
					}
				}
				else
				{
					unit->attack(task.getPosition());
				}
			}
		}
	}
}