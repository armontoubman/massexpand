#pragma once

#include "DefilerMicro.h"
#include <BWAPI.h>
#include "Task.h"
#include "GlobalMicro.h"
#include "Util.h"

DefilerMicro::DefilerMicro()
{
}

DefilerMicro::DefilerMicro(HighCommand* h)
{
	this->hc = h;
}

void DefilerMicro::micro(BWAPI::Unit* unit)
{
	Task task = this->hc->ta->getTaskOfUnit(unit);

	if(unit->isUnderStorm())
	{
		moveToNearestBase(unit);
	}
	else
	{
		if(allEigenUnits().inRadius(dist(10), unit->getPosition()).not(Defiler).size() > 3)
		{
			UnitGroup enemies = allEnemyUnits().inRadius(dist(9), unit->getPosition());
			bool atLeastOneUnderSwarm = false;
			for each(BWAPI::Unit* enemy in enemies)
			{
				if(isUnderDarkSwarm(enemy))
				{
					atLeastOneUnderSwarm = true;
				}
			}
			if(!atLeastOneUnderSwarm)
			{
				int energy = unit->getEnergy();
				int energyneeded = BWAPI::TechTypes::Dark_Swarm.energyUsed();
				if(energy < energyneeded)
				{
					UnitGroup zerglings = allEigenUnits()(Zergling);
					if(zerglings.size() > 0)
					{
						BWAPI::Unit* victim = getNearestUnit(unit->getPosition(), zerglings);
						unit->useTech(BWAPI::TechTypes::Consume, victim);
					}
					else
					{
						unit->move(getNearestUnit(unit->getPosition(), allUnits()(Dark_Swarm))->getPosition());
					}
				}
				else
				{
					UnitGroup enemies = allEnemyUnits();
					UnitGroup enemiesNotUnderSwarm;
					for each(BWAPI::Unit* enemy in enemies)
					{
						if(!isUnderDarkSwarm(enemy))
						{
							enemiesNotUnderSwarm.insert(enemy);
						}
					}
					BWAPI::Unit* nearestEnemyNotUnderSwarm = getNearestUnit(unit->getPosition(), enemiesNotUnderSwarm);
					UnitGroup swarms = allUnits()(Dark_Swarm);
					BWAPI::Unit* nearestSwarm = getNearestUnit(unit->getPosition(), swarms);
					if(nearestEnemyNotUnderSwarm != NULL && nearestSwarm != NULL)
					{
						if(nearestEnemyNotUnderSwarm->getPosition().getDistance(nearestSwarm->getPosition()) > dist(5))
						{
							int x = abs(nearestEnemyNotUnderSwarm->getPosition().x() - nearestSwarm->getPosition().x());
							int y = abs(nearestEnemyNotUnderSwarm->getPosition().y() - nearestSwarm->getPosition().y());
							unit->useTech(BWAPI::TechTypes::Dark_Swarm, BWAPI::Position(x, y));
						}
						else
						{
							unit->useTech(BWAPI::TechTypes::Dark_Swarm, nearestEnemyNotUnderSwarm);
						}
					}
				}
			}
			else
			{
				// nothing
			}
		}
		else
		{
			UnitGroup enemies = allEnemyUnits().inRadius(dist(9), unit->getPosition());
			if(enemies.size() > 0)
			{
				UnitGroup buildings = allEigenUnits()(isBuilding).inRadius(dist(5), unit->getPosition());
				if(buildings.size() > 0)
				{
					unit->useTech(BWAPI::TechTypes::Dark_Swarm, unit);
				}
				else
				{
					moveToNearestBase(unit);
				}
			}
			else
			{
				unit->move(task.getPosition());
			}
		}
	}
}