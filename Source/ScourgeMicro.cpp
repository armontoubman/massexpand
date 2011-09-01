#pragma once

#include "ScourgeMicro.h"
#include <BWAPI.h>
#include "Task.h"
#include "GlobalMicro.h"
#include "Util.h"

ScourgeMicro::ScourgeMicro()
{
}

ScourgeMicro::ScourgeMicro(HighCommand* h)
{
	this->hc = h;
}

void ScourgeMicro::micro(BWAPI::Unit* unit)
{
	Task task = this->hc->ta->getTaskOfUnit(unit);

	UnitGroup airenemies = allEnemyUnits().inRadius(dist(7), unit->getPosition())(isFlyer);
	UnitGroup allenemies = allEnemyUnits().inRadius(dist(7), unit->getPosition());
	if(unit->isUnderStorm() || canAttackAir(allenemies) && airenemies.size() == 0)
	{
		moveToNearestBase(unit);
	}
	else
	{
		if(airenemies.size() > 0)
		{
			if(canAttackAir(allenemies) || airenemies.size() > 2 * allEigenUnits()(Scourge).size())
			{
				unit->move(moveAway(unit));
			}
			else
			{
				UnitGroup scourge = *this->hc->eiugm->getGroupOfUnit(unit);
				for each(BWAPI::Unit* s in scourge)
				{
					if(!this->hc->mm->isUnitMicrod(s))
					{
						s->attack(*airenemies.begin());
						this->hc->mm->unitIsMicrod(s);
					}
				}
			}
		}
		else
		{
			if(unit->getDistance(task.getPosition()) < dist(9))
			{
				unit->move(splitUp(unit));
			}
			else
			{
				unit->move(task.getPosition());
			}
		}
	}
}