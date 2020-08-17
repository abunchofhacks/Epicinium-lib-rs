#pragma once
#include "header.hpp"

#include "floodfill.hpp"

class Bible;
class Board;
class Cell;


class OceanFloodfill : public Floodfill<OceanFloodfill>
{
public:
	OceanFloodfill(const Bible& bible, Board& board);

private:
	const int8_t _maxrow;
	const int8_t _maxcol;

	void map(Cell index);
	void flood(Cell index);
	void reduce(Cell /**/) {}

	friend Floodfill;

public:
	bool ocean(Cell at) const;
};
