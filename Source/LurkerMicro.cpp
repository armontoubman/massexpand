#pragma once

#include "LurkerMicro.h"
#include <BWAPI.h>
#include "Task.h"
#include "GlobalMicro.h"
#include "Util.h"

LurkerMicro::LurkerMicro()
{
}

LurkerMicro::LurkerMicro(HighCommand* h)
{
	this->hc = h;
}

void LurkerMicro::micro(BWAPI::Unit* unit)
{
	Task task = this->hc->ta->getTaskOfUnit(unit);

	if(!unit->isBurrowed())
	{
		if(unit->isUnderStorm())
		{
			moveToNearestBase(unit);
		}
		else
		{
			if(unit->getPosition().getDistance(task.getPosition()) > dist(6) && allEnemyUnits().inRadius(dist(8), unit->getPosition()).size() == 0)
			{
				unit->move(task.getPosition());
			}
			else
			{
				unit->burrow();
			}
		}
	}
	else
	{
		if(unit->isUnderStorm())
		{
			unit->unburrow();
		}
		else
		{
			UnitGroup enemies = allEnemyUnits().inRadius(dist(6), unit->getPosition());
			UnitGroup enemies2 = allEnemyUnits().inRadius(dist(8), unit->getPosition());
			if(enemies2.size() > 0)
			{
				if(!this->hc->eiudm->unitIsSeen(unit))
				{
					if(enemies.size() > 3)
					{
						if(enemies(Marine).size() > 0 || enemies(isWorker).size() > 0 || enemies(Zealot).size() > 0 || enemies(Medic).size() > 0 || enemies(Zergling).size() > 0)
						{
							if(getNearestUnit(unit->getPosition(), enemies)->getPosition().getDistance(unit->getPosition()) < dist(3))
							{
								unit->attack(getNearestUnit(unit->getPosition(), enemies));
							}
							else
							{
								this->hold(unit);
							}
						}
						else
						{
							unit->attack(*enemies.begin());
						}
					}
					else
					{
						UnitGroup structures = allEnemyUnits()(isBuilding);
						if(structures.size() > 0)
						{
							BWAPI::Unit* neareststructure = getNearestUnit(unit->getPosition(), structures);
							if(this->hc->eiugm->getGroupOfUnit(unit)->getCenter().getDistance(neareststructure->getPosition()) < dist(10))
							{
								unit->attack(neareststructure);
							}
						}
					}
				}
				else
				{
					this->hold(unit);
				}
			}
			else
			{
				if(unit->getPosition().getDistance(task.getPosition()) > dist(6))
				{
					unit->unburrow();
				}
				else
				{
					this->hold(unit);
				}
			}
		}
	}
}

void LurkerMicro::hold(BWAPI::Unit* unit)
{
	UnitGroup holdgroup;
	holdgroup.insert(unit);
	UnitGroup overlords = allEigenUnits()(Overlord)(isIdle);
	if(overlords.size() > 0)
	{
		holdgroup.insert(*overlords.begin());
		holdgroup.holdPosition();
	}
}