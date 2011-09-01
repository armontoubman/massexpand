#pragma once

#include "HydraliskMicro.h"
#include <BWAPI.h>
#include "Task.h"
#include "GlobalMicro.h"
#include "Util.h"

HydraliskMicro::HydraliskMicro()
{
}

HydraliskMicro::HydraliskMicro(HighCommand* h)
{
	this->hc = h;
}

void HydraliskMicro::micro(BWAPI::Unit* unit)
{
	Task task = this->hc->ta->getTaskOfUnit(unit);

	if(unit->isUnderStorm())
	{
		moveToNearestBase(unit);
	}
	else
	{
		UnitGroup allMelee = allEnemyUnits()(Drone) + allEnemyUnits()(Zealot) + allEnemyUnits()(Zergling) + allEnemyUnits()(SCV) + allEnemyUnits()(Probe) + allEnemyUnits()(Ultralisk);
		UnitGroup swarms = allUnits()(Dark_Swarm);
		BWAPI::Unit* swarm = getNearestUnit(unit->getPosition(), swarms);
		if(swarm != NULL && swarm->getPosition().getDistance(unit->getPosition()) < dist(10) && allMelee.size() == 0)
		{
			if(!isUnderDarkSwarm(unit))
			{
				unit->attack(swarm->getPosition());
			}
			else
			{
				UnitGroup enemies = allEnemyUnits().inRadius(dist(10), unit->getPosition());
				BWAPI::Unit* target = NULL;
				for each(BWAPI::Unit* u in enemies)
				{
					if(!isUnderDarkSwarm(u))
					{
						target = u;
						break;
					}
				}
				if(target != NULL)
				{
					unit->attack(target);
				}
			}
		}
		else
		{
			if(allEigenUnits()(Hydralisk).inRadius(dist(6), unit->getPosition()).size() > 1)
			{
				int allies = allEigenUnits().inRadius(dist(9), unit->getPosition()).size();
				int enemies = allEnemyUnits().inRadius(dist(8), unit->getPosition()).not(isBuilding).not(isWorker).size();
				if(enemies * 1.5 > allies)
				{
					if(unit->getGroundWeaponCooldown() != 0)
					{
						unit->move(moveAway(unit));
					}
					else
					{
						unit->attack(getNearestUnit(unit->getPosition(), allEnemyUnits().inRadius(dist(15), unit->getPosition())));
					}
				}
				else
				{
					if(unit->getPosition().getDistance(task.getPosition()) > dist(5))
					{
						if(allEnemyUnits().inRadius(dist(6), unit->getPosition()).size() > 0)
						{
							BWAPI::Unit* nearesttarget = getNearestUnit(unit->getPosition(), allEnemyUnits().inRadius(dist(6), unit->getPosition()));
							if(nearesttarget != NULL && nearesttarget->getPosition().getDistance(unit->getPosition()) <= dist(6))
							{
								if(unit->getGroundWeaponCooldown() != 0)
								{
									unit->move(task.getPosition());
								}
								else
								{
									unit->attack(nearesttarget);
								}
							}
							else
							{
								if(unit->getGroundWeaponCooldown() != 0)
								{
									unit->move(task.getPosition());
								}
								else
								{
									BWAPI::Unit* attack3nearest = getNearestUnit(unit->getPosition(), allEnemyUnits());
									if(attack3nearest != NULL)
									{
										unit->attack(attack3nearest);
									}
									else
									{
										unit->move(task.getPosition());
									}
								}
							}
						}
						else
						{
							unit->attack(task.getPosition());
						}
					}
					else
					{
						if(allEnemyUnits().inRadius(dist(6), unit->getPosition()).size() > 0)
						{
							BWAPI::Unit* nearesttarget = getNearestUnit(unit->getPosition(), allEnemyUnits().inRadius(dist(6), unit->getPosition()));
							if(nearesttarget != NULL && nearesttarget->getDistance(unit->getPosition()) <= dist(6))
							{
								if(unit->getGroundWeaponCooldown() != 0)
								{
									unit->move(moveAway(unit));
								}
								else
								{
									unit->attack(nearesttarget);
								}
							}
							else
							{
								if(unit->getGroundWeaponCooldown() != 0)
								{
									unit->move(moveAway(unit));
								}
								else
								{
									nearesttarget = getNearestUnit(unit->getPosition(), allEnemyUnits());
									if(nearesttarget != NULL)
									{
										unit->attack(nearesttarget);
									}
								}
							}
						}
						else
						{
							unit->move(moveAway(unit));
						}
					}
				}
			}
			else
			{
				UnitGroup nearEnemies = allEnemyUnits().inRadius(dist(9), unit->getPosition());
				if(nearEnemies.size() > 0 && canAttackGround(nearEnemies))
				{
					unit->attack(getNearestUnit(unit->getPosition(), nearEnemies));
				}
				else
				{
					UnitGroup ug = *this->hc->eiugm->getGroupOfUnit(unit);
					if(tooSplitUp(dist(8), ug))
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
	}
}