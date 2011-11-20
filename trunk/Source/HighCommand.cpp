#pragma once
#include "HighCommand.h"

#include "EigenUnitDataManager.h"
#include "EnemyUnitDataManager.h"
#include "MicroManager.h"
#include "EigenUnitGroupManager.h"
#include "TaskManager.h"
#include "TaskAssigner.h"
#include "ResourceManager.h"
#include "ProductionManager.h"
#include "ConstructionManager.h"
#include "ContractManager.h"

#include <BWAPI.h>
#include "Util.h"
#include "UnitGroup.h"
#include <time.h>
#include <boost/format.hpp>
#include "Logger.h"

HighCommand::HighCommand()
{

	Broodwar->setLocalSpeed(0); // WEGHALEN IN FINAL
	this->startLog();

	this->home = BWAPI::Broodwar->self()->getStartLocation();

	this->eiudm = new EigenUnitDataManager(this);
	this->eudm = new EnemyUnitDataManager(this);
	this->mm = new MicroManager(this);
	this->eiugm = new EigenUnitGroupManager(this);
	this->tm = new TaskManager(this);
	this->ta = new TaskAssigner(this);
	this->rm = new ResourceManager(this);
	this->pm = new ProductionManager(this);
	this->csm = new ConstructionManager(this);
	this->ctm = new ContractManager(this);

}

HighCommand::~HighCommand() {
	delete this->eiudm;
	delete this->eudm;
	delete this->mm;
	delete this->eiugm;
	delete this->tm;
	delete this->ta;
	delete this->rm;
	delete this->pm;
	delete this->csm;
	delete this->ctm;
}

void HighCommand::startLog()
{
	Logger::getInstance()->info("HC: New game");
}

void HighCommand::update()
{
	//Logger::getInstance()->info("HC: eiudm->update()");
	this->eiudm->update();
	//Logger::getInstance()->info("HC: eiugm->update()");
	this->eiugm->update();
	//Logger::getInstance()->info("HC: rm->update()");
	this->rm->update();
	//Logger::getInstance()->info("HC: eudm->update()");
	this->eudm->update();
	
	//Logger::getInstance()->info("HC: pm->update()");
	this->pm->update();
	//Logger::getInstance()->info("HC: csm->update()");
	this->csm->update();
	//Logger::getInstance()->info("HC: ctm->update()");
	this->ctm->update();
	
	//Logger::getInstance()->info("HC: tm->update()");
	this->tm->update();
	//Logger::getInstance()->info("HC: ta->update()");
	this->ta->update();
	
	//Logger::getInstance()->info("HC: mm->update()");
	this->mm->update();

	this->drawFPS();
	this->drawTasks();
	this->drawUnits();
	this->drawRightPanel();
}

/*void HighCommand::tic()
{
	this->c = clock();
}

float HighCommand::toc()
{
	return ((static_cast<float>(clock()-(this->c))/CLOCKS_PER_SEC)*1000);
}

void HighCommand::logtimes()
{
	std::string output = "";
	output.append(floatToString(times[0])).append(",");
	output.append(floatToString(times[1])).append(",");
	output.append(floatToString(times[2])).append(",");
	output.append(floatToString(times[3])).append(",");
	output.append(floatToString(times[4])).append(",");
	output.append(floatToString(times[5])).append(",");
	output.append(floatToString(times[6])).append(",");
	output.append(floatToString(times[7])).append("\n");
	log(output.c_str());
}*/

void HighCommand::onStart()
{
	this->rm->onStart();
}

std::string HighCommand::chat()
{
	std::string s;
	s = boost::str( boost::format( "HC: %d FPS / %d avg FPS" ) % Broodwar->getFPS() % Broodwar->getAverageFPS() );
	return s;
}

void HighCommand::onUnitDiscover(Unit* u)
{
	this->eudm->onUnitDiscover(u);
}

void HighCommand::onUnitEvade(Unit* u)
{
	this->eudm->onUnitEvade(u);
}

void HighCommand::onUnitShow(Unit* u)
{
}

void HighCommand::onUnitHide(Unit* u)
{
}

void HighCommand::onUnitCreate(Unit* u)
{
	this->eiugm->onUnitCreate(u);
}

void HighCommand::onUnitDestroy(Unit* u)
{
	this->eudm->onUnitDestroy(u);
	this->rm->onUnitDestroy(u);
	this->eiugm->onUnitDestroy(u);
	this->ta->onUnitDestroy(u);
	this->ctm->onUnitDestroy(u);

	Broodwar->printf("onUnitDestroy %s", u->getType().getName().c_str());
}

void HighCommand::onUnitMorph(Unit* u)
{
	this->eudm->onUnitMorph(u);
	this->eiugm->onUnitMorph(u);
	this->rm->onUnitMorph(u);
	this->ta->onUnitMorph(u);
	this->ctm->onUnitMorph(u);

	Broodwar->printf("onUnitMorph %s", u->getType().getName().c_str());
}

void HighCommand::onUnitRenegade(Unit* u)
{
	this->eiudm->onUnitRenegade(u);
	this->eiugm->onUnitRenegade(u);
}

void HighCommand::drawFPS()
{
	Broodwar->drawTextScreen(100,0,"%d FPS",Broodwar->getFPS());
}

void HighCommand::drawTasks()
{
	std::map<TaskType, std::list<Task>> tasklists = this->tm->getTasklists();
	for each(std::pair<TaskType, std::list<Task>> typepair in tasklists)
	{
		for each(Task t in typepair.second)
		{
			int x = t.getPosition().x();
			int y = t.getPosition().y();
			Broodwar->drawCircleMap(x,y,32,Colors::White,false);
			Broodwar->drawTextMap(x,y,t.getTypeName().c_str());
		}
	}

	std::map<UnitGroup*, Task> plan = this->ta->getPlan();
	for each(std::pair<UnitGroup*, Task> assignment in plan)
	{
		for(std::set<BWAPI::Unit*>::const_iterator i=assignment.first->begin();i!=assignment.first->end();i++)
		{
			int x1 = (*i)->getPosition().x();
			int y1 = (*i)->getPosition().y();
			int x2 = assignment.second.getPosition().x();
			int y2 = assignment.second.getPosition().y();
			BWAPI::Broodwar->drawLineMap(x1, y1, x2, y2, Colors::White);
		}
	}

	std::map<BWAPI::Unit*, Task> dronePlan = this->ta->getDronePlan();
	for each(std::pair<BWAPI::Unit*, Task> assignment in dronePlan)
	{
		int x1 = assignment.first->getPosition().x();
		int y1 = assignment.first->getPosition().y();
		int x2 = assignment.second.getPosition().x();
		int y2 = assignment.second.getPosition().y();
		BWAPI::Broodwar->drawLineMap(x1, y1, x2, y2, Colors::White);
	}
}

void HighCommand::drawUnits()
{
	for each(Unit* u in Broodwar->self()->getUnits())
	{
		int x = u->getPosition().x();
		int y = u->getPosition().y();
		Broodwar->drawTextMap(x,y,u->getOrder().getName().c_str());
	}
}

void HighCommand::drawRightPanel()
{
	int x = 500;
	int y = 16;
	int yoffset = 25;

	int line = 1;

	Broodwar->drawTextScreen(x,yoffset+y*line, "", true);
	line++;
	Broodwar->drawTextScreen(x,yoffset+y*line,"BuildList %i", this->pm->getStep());
	line++;
	for each(Product p in this->pm->getBuildList()->productList)
	{
		Broodwar->drawTextScreen(x,yoffset+y*line,"%s",p.buildtype.getName().c_str());
		line++;
	}
	line++;
	Broodwar->drawTextScreen(x,yoffset+y*line,"Contracts");
	line++;
	for each(Contract c in this->ctm->getContractList())
	{
		Broodwar->drawTextScreen(x,yoffset+y*line,"%d %s",c.drone, c.unittype.getName().c_str());
		line++;
    }

	x = 400;
	line = 1;
	Broodwar->drawTextScreen(x,yoffset+y*line, "", true);
	line++;
	Broodwar->drawTextScreen(x,yoffset+y*line,"Counters");
	line++;
	//for each(std::pair<BWAPI::UnitType, int> pair in this->pm->getBuildList()->unittypeCounter)
	//{
		//Broodwar->drawTextScreen(x,yoffset+y*line,"%s %i",pair.first.getName().c_str(), pair.second);
		//line++;
	//}
	Broodwar->drawTextScreen(x,yoffset+y*line,"%i expands", this->pm->getBuildList()->expandCounter);
}