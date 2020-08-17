#pragma once
#include "header.hpp"

#include "randomizer.hpp"
#include "cell.hpp"

class Bible;
class Board;
class ChangeSet;
enum class Season : uint8_t;


class ChaosTransition
{
public:
	ChaosTransition(const Bible& bible, Board& board, ChangeSet& changeset);

private:
	const Bible& _bible;
	Board& _board;
	ChangeSet& _changeset;

	int _remainder;

	Randomizer<Cell> _randompositions;

	void map(Cell index);
	void enact(Cell index);

	void distribute(int amount);

	void fillRandomPositions();

public:
	void execute();
};
