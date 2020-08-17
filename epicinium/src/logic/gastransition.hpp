#pragma once
#include "header.hpp"

class Bible;
class Board;
class ChangeSet;
class Cell;


class GasTransition
{
public:
	GasTransition(const Bible& bible, Board& board, ChangeSet& changeset);

private:
	const Bible& _bible;
	Board& _board;
	ChangeSet& _changeset;

	std::vector<uint8_t> _results;

	void map(Cell index);
	void reduce(Cell index);

	void put(Cell index, int8_t level);

public:
	void execute();
};
