#pragma once
#include "header.hpp"

class Bible;
class Board;
class ChangeSet;
class Cell;


class RadiationTransition
{
public:
	RadiationTransition(Board& board, ChangeSet& changeset);

private:
	Board& _board;
	ChangeSet& _changeset;

	std::vector<uint8_t> _results;

	void map(Cell index);
	void reduce(Cell index);

	bool source(Cell index, int8_t level);
	bool fed(Cell index, int8_t level);
	bool cuddled(Cell index, int8_t level);
	bool saturated(Cell index, int8_t level);

	void spread(Cell index, int8_t level, int8_t times);

	void put(Cell index, int8_t level);

public:
	void execute();
};
