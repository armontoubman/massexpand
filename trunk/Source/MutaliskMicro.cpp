#pragma once

#include "MutaliskMicro.h"
#include <BWAPI.h>
#include "Task.h"
#include "GlobalMicro.h"
#include "Util.h"

MutaliskMicro::MutaliskMicro()
{
}

MutaliskMicro::MutaliskMicro(HighCommand* h)
{
	this->hc = h;
}

void MutaliskMicro::micro(BWAPI::Unit* unit)
{
	Task task = this->hc->ta->getTaskOfUnit(unit);
	
	if(unit->isUnderStorm())
	{
		moveToNearestBase(unit);
	}
	else
	{
		if(unit->getGroundWeaponCooldown() >= 15 || unit->getAirWeaponCooldown() >= 15)
		{
			if(canAttackAir(allEnemyUnits().inRadius(dist(8), unit->getPosition())))
			{
				unit->move(moveAway(unit));
			}
			else
			{
				if(unit->getDistance(task.getPosition()) < dist(5))
				{
					moveToNearestBase(unit);
				}
				else
				{
					UnitGroup ug = *this->hc->eiugm->getGroupOfUnit(unit);
					if(tooSplitUp(dist(3), ug))
					{
						unit->attack(getNearestUnit(ug.getCenter(), ug)->getPosition());
					}
					else
					{
						unit->attack(task.getPosition());
					}
				}
			}
		}
		else
		{
			UnitGroup enemies = allEnemyUnits().inRadius(dist(7), unit->getPosition());
			UnitGroup enemiesMilitary = enemies.not(isBuilding);
			if(enemiesMilitary.size() > 0)
			{
				BWAPI::Unit* nearest = getNearestUnit(unit->getPosition(), enemiesMilitary);
				if(nearest->getDistance(unit->getPosition()) < dist(4))
				{
					unit->attack(nearest);
				}
				else
				{
					unit->attack(nearest->getPosition());
				}
			}
			else
			{
				if(enemies.size() > 0)
				{
					BWAPI::Unit* nearest = getNearestUnit(unit->getPosition(), enemies);
					if(nearest->getDistance(unit->getPosition()) < dist(4))
					{
						unit->attack(nearest);
					}
					else
					{
						unit->attack(nearest->getPosition());
					}
				}
				else
				{
					if(unit->getDistance(task.getPosition()) <= dist(1))
					{
						moveToNearestBase(unit);
					}
					else
					{
						UnitGroup ug = *this->hc->eiugm->getGroupOfUnit(unit);
						if(tooSplitUp(dist(6), ug))
						{
							moveToNearestBase(unit);
						}
						else
						{
							unit->attack(task.getPosition());
						}
					}
				}
			}
		}
	}
}