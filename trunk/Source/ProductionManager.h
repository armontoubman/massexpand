#pragma once
#include <BWAPI.h>
#include "ProductList.h"
#include "UnitGroup.h"
class HighCommand;

using namespace BWAPI;

/**
 * The ProductionManager decides what units/buildings, tech and upgrades we want and which we should be building right now.
 * \see ProductList
 * \see Product
 */
class ProductionManager
{
public:
	ProductionManager(HighCommand* h);
	void update();
	ProductList* getWantList();
	ProductList* getBuildList();
	int getStep();
private:
	HighCommand* hc;

	/**
	 * The wantList holds the Products that we want to have.
	 */
	ProductList wantList;

	/**
	 * The buildList is the queue of Products that are up for construction.
	 */
	ProductList buildList;

	/**
	 * The phase of the game in terms of units we want and have.
	 */
	int step;

	/* update lists */

	/**
	 * Check the race of our enemy and use the appropriate building orders and orders for reinforcements.
	 */
	void updateLists();

	/**
	 * Building order against a Protoss enemy.
	 */
	void updateListsAgainstProtoss();

	/**
	 * Building order against a Protoss enemy regardless of the current step.
	 */
	void updateListsAgainstProtossReinforcements();

	/**
	 * Building order against a Terran enemy.
	 */
	void updateListsAgainstTerran();

	/**
	 * Building order against a Terran enemy regardless of the current step.
	 */
	void updateListsAgainstTerranReinforcements();

	/**
	 * Building order against a Zerg enemy.
	 */
	void updateListsAgainstZerg();

	/**
	 * Building order against a Zerg enemy regardless of the current step.
	 */
	void updateListsAgainstZergReinforcements();

	/**
	 * Building order for upgrades.
	 */
	void updateListsUpgrades();

	/**
	 * General building order, regardless of enemy.
	 */
	void updateListsGeneral();

	/**
	 * If there is something in our wantList that we don't have, queue it for construction.
	 */
	void updateListsGenericRule();
	/* end update lists */

	/* ProductList interface */
	void addWant(BWAPI::UnitType unittype);
	void addWant(BWAPI::UnitType unittype, int amount);
	void addWant(BWAPI::TechType techtype);
	void addWant(BWAPI::UpgradeType upgradetype);
	void addBuild(BWAPI::UnitType unittype);
	void addBuild(BWAPI::UnitType unittype, int amount);
	void addBuild(BWAPI::TechType techtype);
	void addBuild(BWAPI::UpgradeType upgradetype);
	void addBuildTop(BWAPI::UnitType unittype);
	bool wantListContains(BWAPI::UnitType unittype);
	bool buildListContains(BWAPI::UnitType unittype);
	/* end ProductList interface */

	/* intel */
	int nrOfEnemy(BWAPI::UnitType unittype);
	int nrOfOwn(BWAPI::UnitType unittype);
	int nrOfEnemyBases();
	int nrOfOwnBasesWithMinerals();
	UnitGroup getOwnBasesWithMinerals();
	int nrOfOwnMilitaryUnits();
	int nrOfEnemyMilitaryUnits();
	int countEggsMorphingInto(BWAPI::UnitType unittype);
	int nrOfOwnMorphing(BWAPI::UnitType unittype);
	/* end intel */

	/**
	 * Queues an expand in the buildList.
	 */
	void buildExpand();

	/**
	 * Calculate how many drones we should build given the number of mineral deposits and gas extractors.
	 */
	int nrOfExtraDronesRequired();
	bool wantListIsCompleted();
};