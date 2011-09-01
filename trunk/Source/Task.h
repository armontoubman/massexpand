#pragma once
#include <BWAPI.h>
#include "UnitGroup.h"

using namespace BWAPI;

/**
 * All possible types of Tasks.
 */
enum TaskType
{
	NoTask,
	ScoutTask,
	CombatTask,
	PrepareTask,
	DetectorTask,
	DefendTask,
	GatherMineralsTask,
	GatherGasTask
};

/**
 * The Task class.
 * A Task is an objective which is assigned to a UnitGroup.
 */
class Task {
public:

	/**
	 * Default constructor. Creates a Task with type NoTask and Position::None.
	 */
	Task();

	/**
	 * Constructor for creating a Task with a specific type and position.
	 */
	Task(TaskType t, Position pos);

	/**
	 * Constructor for creating a Task with a specific type, position and target unit.
	 */
	Task(TaskType t, Position pos, Unit* target);

	/**
	 * Equality comparison operator.
	 */
	bool operator==(const Task& param) const;

	/**
	 * Order comparison operator (not used).
	 */
	bool operator<(const Task& rhs) const;

	TaskType getType();
	Position getPosition();
	Unit* getTarget();

	/**
	 * \return String representation of the type of the Task.
	 */
	std::string getTypeName();

	/**
	 * \return String representation of the type of the given TaskType.
	 */
	std::string getTypeName(TaskType t);
private:
	TaskType type;
	Position position;
	Unit* target;
};