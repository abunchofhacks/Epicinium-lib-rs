#pragma once
#include "header.hpp"

class Bible;
class Board;
class ChangeSet;
class Cell;


class PowerTransition
{
public:
	enum class Stage : uint8_t
	{
		ALL = 0,
		NICENESS,
		LABOR,
		ENERGY,
	};

	PowerTransition(const Bible& bible, Board& board, ChangeSet& changeset,
		Stage stage);

private:
	const Bible& _bible;
	Board& _board;
	ChangeSet& _changeset;

	Stage _stage;

	std::vector<uint8_t> _results;

	void map(Cell index);
	void reduce(Cell index);

	int evaluateNiceness(Cell index);
	int evaluateLabor(Cell index);
	int evaluateEnergy(Cell index);

public:
	void execute();

	static constexpr Stage stages[3] = {Stage::NICENESS, Stage::LABOR, Stage::ENERGY};
};
