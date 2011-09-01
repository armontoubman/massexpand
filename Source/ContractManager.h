#pragma once
#include <BWAPI.h>
#include "HighCommand.h"
class HighCommand;

using namespace BWAPI;

/**
 * The Contract class is a link between a Drone and the type of building it should build. Contracted drones should proceed to a suitable building site and morph into the desired unittype.
 */
struct Contract
{
	/**
	 * The contracted drone.
	 */
	BWAPI::Unit* drone;

	/**
	 * The desired type of building. If unittype is None, the desired building is a Hatchery at an expansion site.
	 */
	BWAPI::UnitType unittype;

	/**
	 * Constructor creating an empty contract.
	 */
	Contract()
	{
		drone = NULL;
		unittype = BWAPI::UnitTypes::Unknown;
	}
	
	/**
	 * Equality comparison operator.
	 */
	bool operator==(const Contract& l)
	{
		return ((l.drone == drone) && (l.unittype == unittype));
	}
};

/**
 * The ContractManager manages Contracts. It takes orders for new buildings and hires available drones. It also finds suitable building sites.
 */
class ContractManager
{
public:
	ContractManager(HighCommand* h);
	void update();

	/**
	 * If a contracted Drone is destroyed, a new Drone should replace it.
	 */
	void onUnitDestroy(BWAPI::Unit* u);
	
	/**
	 * If a Drone morphs into the building it was contracted for, the contract should be removed.
	 */
	void onUnitMorph(BWAPI::Unit* u);

	/**
	 * Check if a certain drone is contracted.
	 */
	bool isContracted(BWAPI::Unit* drone);

	/**
	 * Count the number of contracts for buildings of type unittype.
	 */
	int count(BWAPI::UnitType unittype);

	/**
	 * Count the number of contracts for expands.
	 */
	int countExpand();

	/**
	 * Create a new contract for the desired unittype.
	 */
	void newContract(BWAPI::UnitType unittype);

	/**
	 * Create a new contract for an expand.
	 */
	void newExpandContract();

	/**
	 * Get the contract of Drone drone.
	 * \return a new empty Contract if the drone is not contracted.
	 */
	Contract getContract(BWAPI::Unit* drone);

	/**
	 * Find a suitable building site for a building of type unittype.
	 */
	BWAPI::TilePosition findPositionFor(BWAPI::UnitType unittype);

	/**
	 * Find a suitable building site for a new expand: a baselocation, unused, and nearest to our main base.
	 */
	BWAPI::TilePosition findPositionForExpand();

	/**
	 * Get the list with all Contracts.
	 */
	std::list<Contract> getContractList();

	/**
	 * Get the total gas price of all the buildings we have Contracts for.
	 */
	int getTotalGas();

	/**
	 * Get the total mineral price of all the buildings we have Contracts for.
	 */
	int getTotalMinerals();
private:
	HighCommand* hc;
	std::list<Contract> contractList;

	/**
	 * Finds a Drone that is not carrying any minerals or gas.
	 * \return NULL if no such Drone is available at the current frame.
	 */
	BWAPI::Unit* findAvailableDrone();

	/**
	 * Removes the first Contract found for a building of type unittype.
	 */
	void removeContract(BWAPI::UnitType unittype);
};