#pragma once
#include <BWAPI.h>

#include "EigenUnitDataManager.h"
class EigenUnitDataManager;
#include "EnemyUnitDataManager.h"
class EnemyUnitDataManager;
#include "MicroManager.h"
class MicroManager;
#include "EigenUnitGroupManager.h"
class EigenUnitGroupManager;
#include "TaskManager.h"
class TaskManager;
#include "TaskAssigner.h"
class TaskAssigner;
#include "ResourceManager.h"
class ResourceManager;

#include "ProductionManager.h"
class ProductionManager;
#include "ConstructionManager.h"
class ConstructionManager;
#include "ContractManager.h"
class ContractManager;

#include <time.h>

using namespace BWAPI;

/**
 * The HighCommand class is the control center of MassExpand. It contains the main update loop and event listeners. It also controls and notifies all the managers.
 * The drawing of additional information on the screen is also done here.
 */
class HighCommand
{
public:
	/**
	 * Constructor. Creates all the managers.
	 */
	HighCommand();
	~HighCommand();

	/**
	 * The main game loop. All managers' update functions are called here.
	 */
	void update();
	void onStart();
	void onUnitDiscover(Unit* u);
	void onUnitEvade(Unit* u);
	void onUnitShow(Unit* u);
	void onUnitHide(Unit* u);
	void onUnitCreate(Unit* u);
	void onUnitDestroy(Unit* u);
	void onUnitMorph(Unit* u);
	void onUnitRenegade(Unit* u);

	std::string chat();

	EigenUnitDataManager* eiudm;
	EnemyUnitDataManager* eudm;
	MicroManager* mm;
	EigenUnitGroupManager* eiugm;
	TaskManager* tm;
	TaskAssigner* ta;
	ResourceManager* rm;
	ProductionManager* pm;
	ConstructionManager* csm;
	ContractManager* ctm;

	/**
	 * The TilePosition of our starting base location.
	 */
	BWAPI::TilePosition home;

private:
	void startLog();

	/*void tic();
	float toc();
	float c;
	std::map<int, float> times;
	void logtimes();*/

	/**
	 * Draws the current number of frames per second on the screen.
	 */
	void drawFPS();

	/**
	 * Draws circles and tasktypes around the positions of Tasks.
	 */
	void drawTasks();

	/**
	 * Draws additional information around units.
	 */
	void drawUnits();

	/**
	 * Draws additional information on the right side of the screen.
	 */
	void drawRightPanel();
};