#include "oceanfloodfill.hpp"
#include "source.hpp"

#include "bible.hpp"
#include "board.hpp"
#include "tiletoken.hpp"
#include "position.hpp"
#include "move.hpp"



OceanFloodfill::OceanFloodfill(const Bible& bible, Board& board) :
	Floodfill(bible, board),
	_maxrow(board.rows() - 1),
	_maxcol(board.cols() - 1)
{}

void OceanFloodfill::map(Cell index)
{
	Position pos = index.pos();
	if (pos.row == 0 || pos.row == _maxrow || pos.col == 0 || pos.col == _maxcol)
	{
		if (_bible.tileWater(_board.tile(index).type))
		{
			put(index);
		}
	}
}

void OceanFloodfill::flood(Cell from)
{
	for (const Move& move : {Move::E, Move::S, Move::W, Move::N})
	{
		Cell to = from + move;
		if (_bible.tileWater(_board.tile(to).type))
		{
			put(from, to);
		}
	}
}

bool OceanFloodfill::ocean(Cell at) const
{
	return get(at) != uint16_t(-1);
}
