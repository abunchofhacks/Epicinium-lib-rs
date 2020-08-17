#pragma once
#include "header.hpp"

#include "oceanfloodfill.hpp"

class Bible;
class Board;
class ChangeSet;
class Cell;


class ElevationTransition
{
public:
	ElevationTransition(const Bible& bible, Board& board, ChangeSet& changeset);

private:
	const Bible& _bible;
	Board& _board;
	ChangeSet& _changeset;

	OceanFloodfill _oceans;

	std::vector<uint8_t> _elev;
	std::vector<uint8_t> _coast;

	void map(Cell index);
	void reduce(Cell index);

public:
	void execute();
};
