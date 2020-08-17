#include "pathingflowfield.hpp"
#include "source.hpp"

#include "bible.hpp"


void PathingFlowfield::flood(Cell from)
{
	std::vector<Move> moves = {Move::E, Move::S, Move::W, Move::N};
	std::random_shuffle(moves.begin(), moves.end());
	for (const Move& move : moves)
	{
		Cell to = from + move;
		TileType tiletype = _board.tile(to).type;

		if (tiletype == TileType::NONE) continue;

		if (!forced() && _bible.tileAccessible(tiletype)
			&& (_air || _bible.tileWalkable(tiletype)))
		{
			put(to, ::flip(move));
		}
		else
		{
			force(to, ::flip(move));
		}
	}
}
