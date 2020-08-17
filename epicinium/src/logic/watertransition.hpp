#pragma once
#include "header.hpp"

#include "oceanfloodfill.hpp"

class Bible;
class Board;
class ChangeSet;
class Cell;


class WaterTransition
{
public:
	WaterTransition(const Bible& bible, Board& board, ChangeSet& changeset);

private:
	const Bible& _bible;
	Board& _board;
	ChangeSet& _changeset;

	OceanFloodfill _oceans;

	std::vector<uint8_t> _gain;
	std::vector<uint8_t> _loss;

	void map(Cell index);
	void reduce(Cell index);

	void put(Cell index, int8_t gainorloss);

public:
	void execute();
};
