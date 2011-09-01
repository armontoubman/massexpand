#pragma once
#include <BWAPI.h>
#include "HighCommand.h"
class HighCommand;

using namespace BWAPI;

/**
 * The ConstructionManager class coordinates construction of units and buildings, research and upgrades.
 */
class ConstructionManager
{
public:
	ConstructionManager(HighCommand* h);
	void update();
private:
	HighCommand* hc;

	/**
	 * Internal gas counter. Resets each frame. Used to calculate how many units/buildings/techs/upgrades we can buy in the same frame.
	 */
	int gas;

	/**
	 * Internal minerals counter. Resets each frame. Used to calculate how many units/buildings/techs/upgrades we can buy in the same frame.
	 */
	int minerals;

	/**
	 * Internal supply (total) counter. Resets each frame. Used to calculate how many units/buildings/techs/upgrades we can buy in the same frame.
	 */
	int supplyTotal;
	
	/**
	 * Internal supply (used) counter. Resets each frame. Used to calculate how many units/buildings/techs/upgrades we can buy in the same frame.
	 */
	int supplyUsed;

	/**
	 * Check if the requirements for a Product are satisfied. The requirements depend on whether the Product is a unit/building, tech or upgrade.
	 */
	bool requirementsSatisfied(Product p);

	/**
	 * Check if the requirements for building a unit/building of type unittype are satisfied.
	 *		- We must have at least one of each of the units required to build unittype.
	 *		- If unittype is Lurker or Lurker_Egg, we must have research Lurker_Aspect.
	 */
	bool requirementsSatisfied(BWAPI::UnitType unittype);

	/**
	 * Check if the requirements for researching techtype are satisfied.
	 *		- We must have at least one of the units that researches techtype.
	 */
	bool requirementsSatisfied(BWAPI::TechType techtype);

	/**
	 * Check if the requirements for upgrading upgradetype are satisfied.
	 *		- We must have at least one of the units that upgrades upgradetype.
	 */
	bool requirementsSatisfied(BWAPI::UpgradeType upgradetype);

	/**
	 * Call the right processing function for Product p based on its ProductType.
	 */
	bool process(Product p);

	/**
	 * Divide Products that are units or buildings and call the right processing function.
	 */
	bool processBuild(Product p);

	/**
	 * See if we can afford Product p and if its requirements are satisfied. If so, order the right unit to research it.
	 * \return true if we can afford the Product, its requirements are satisfied and the research order is given.
	 */
	bool processTech(Product p);

	/**
	 * See if we can afford Product p and if its requirements are satisfied. If so, order the right unit to upgrade it.
	 * \return true if we can afford the Product, its requirements are satisfied and the upgrade order is given.
	 */
	bool processUpgrade(Product p);

	/**
	 * See if we can afford a Hatchery and if its requirements are satisfied. If so, tell ContractManager to make a new Contract.
	 * \return true if we can afford the Product, its requirements are satisfied and the Contract is made.
	 */
	bool processExpand(Product p);

	/**
	 * See if we can afford Product p and if its requirements are satisfied. If so, tell ContractManager to make a new Contract.
	 * \return true if we can afford the Product, its requirements are satisfied and the Contract is made.
	 */
	bool processBuilding(Product p);

	/**
	 * See if we can afford Product p and if its requirements are satisfied. If so, morph an Egg to the Product's unittype.
	 * \return true if we can afford the Product, its requirements are satisfied and the morph order is given.
	 */
	bool processUnit(Product p);

	/**
	 * See if we can afford a Lair or Hive and if its requirements are satisfied. If so, morph a Hatchery/Lair.
	 * \return true if we can afford the Product, its requirements are satisfied and the morph order is given.
	 */
	bool processHatcheryUpgrade();

	/**
	 * Check if we can afford the Product with the internal counters of gas, minerals and supply.
	 */
	bool canAfford(Product p);

	/**
	 * Update the internal counters of gas, minerals and supply to reflect that we have given the order to process the Product.
	 */
	void buy(Product p);
};