#pragma once
#include "MicroManager.h"

#include <BWAPI.h>
#include "UnitGroup.h"
#include "HighCommand.h"

#include "DefilerMicro.h"
#include "DroneMicro.h"
#include "HydraliskMicro.h"
#include "LurkerMicro.h"
#include "OverlordMicro.h"
#include "UltraliskMicro.h"
#include "ZerglingMicro.h"

MicroManager::MicroManager(HighCommand* h)
{
	this->hc = h;

	this->defilerMicro = new DefilerMicro(h);
	this->droneMicro = new DroneMicro(h);
	this->hydraliskMicro = new HydraliskMicro(h);
	this->lurkerMicro = new LurkerMicro(h);
	this->overlordMicro = new OverlordMicro(h);
	this->ultraliskMicro = new UltraliskMicro(h);
	this->zerglingMicro = new ZerglingMicro(h);
}

void MicroManager::update()
{
	this->microdUnits.clear();
	std::set<UnitGroup*> ugs = this->hc->eiugm->getUnitGroupSet();
	ugs.insert(this->hc->eiugm->getDroneUG());
	for each(UnitGroup* ug in ugs)
	{
		for(std::set<BWAPI::Unit*>::const_iterator i=ug->begin();i!=ug->end();i++)
		{
			if(!this->isUnitMicrod((*i)))
			{
				this->selectMicro((*i));
				this->unitIsMicrod((*i));
			}
		}
	}
}

void MicroManager::selectMicro(BWAPI::Unit* unit)
{
	if(unit->getType() == BWAPI::UnitTypes::Zerg_Defiler)
	{
		this->defilerMicro->micro(unit);
		return;
	}
	if(unit->getType() == BWAPI::UnitTypes::Zerg_Drone)
	{
		this->droneMicro->micro(unit);
		return;
	}
	if(unit->getType() == BWAPI::UnitTypes::Zerg_Hydralisk)
	{
		this->hydraliskMicro->micro(unit);
		return;
	}
	if(unit->getType() == BWAPI::UnitTypes::Zerg_Lurker)
	{
		this->lurkerMicro->micro(unit);
		return;
	}
	if(unit->getType() == BWAPI::UnitTypes::Zerg_Overlord)
	{
		this->overlordMicro->micro(unit);
		return;
	}
	if(unit->getType() == BWAPI::UnitTypes::Zerg_Ultralisk)
	{
		this->ultraliskMicro->micro(unit);
		return;
	}
	if(unit->getType() == BWAPI::UnitTypes::Zerg_Zergling)
	{
		this->zerglingMicro->micro(unit);
		return;
	}
}

bool MicroManager::isUnitMicrod(BWAPI::Unit* unit)
{
	if(this->microdUnits.contains(unit))
	{
		return true;
	}
	return false;
}

void MicroManager::unitIsMicrod(BWAPI::Unit* unit)
{
	this->microdUnits.insert(unit);
}