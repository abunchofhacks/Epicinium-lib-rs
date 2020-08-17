#include "radiationtransition.hpp"
#include "source.hpp"

#include "board.hpp"
#include "changeset.hpp"
#include "randomizer.hpp"
#include "cell.hpp"


RadiationTransition::RadiationTransition(Board& board, ChangeSet& changeset) :
	_board(board),
	_changeset(changeset),
	_results(_board.end().ix(), 0)
{}

void RadiationTransition::execute()
{
	for (Cell index : _board)
	{
		map(index);
	}

	for (Cell index : _board)
	{
		reduce(index);
	}
}

void RadiationTransition::map(Cell index)
{
	int8_t level = _board.radiation(index);

	if (!level) return;

	if (fed(index, level))
	{
		put(index, level);
		spread(index, level, 1);
		spread(index, level - 1, 8);
	}
	else if (cuddled(index, level))
	{
		put(index, level);
		spread(index, level - 1, 8);
	}
	else if (saturated(index, level))
	{
		put(index, level - 1);
	}
	else if (source(index, level))
	{
		put(index, level);
		spread(index, level - 1, 2);
		spread(index, level - 2, 8);
	}
	else
	{
		put(index, level);
		spread(index, level - 1, 2);
	}
}

void RadiationTransition::reduce(Cell index)
{
	if (!_results[index.ix()]) return;

	// Inside _results, levels are increased by 1 so that 0 means undefined.
	int8_t level = _results[index.ix()] - 1;

	int8_t diff = level - _board.radiation(index);
	if (diff)
	{
		Change change(Change::Type::RADIATION, Descriptor::cell(index.pos()));
		change.xRadiation(diff);
		_board.enact(change);
		_changeset.push(change, _board.vision(index));
	}
}

bool RadiationTransition::source(Cell /**/, int8_t level)
{
	return level >= 3;
}

bool RadiationTransition::fed(Cell index, int8_t level)
{
	for (Cell neighbor : {
			index + Move::E,
			index + Move::E + Move::S,
			index + Move::S,
			index + Move::S + Move::W,
			index + Move::W,
			index + Move::W + Move::N,
			index + Move::N,
			index + Move::N + Move::E,
		})
	{
		if (_board.radiation(neighbor) > level)
		{
			return true;
		}
	}
	return false;
}

bool RadiationTransition::cuddled(Cell index, int8_t level)
{
	int count = 0;
	for (Cell neighbor : {
			index + Move::E,
			index + Move::E + Move::S,
			index + Move::S,
			index + Move::S + Move::W,
			index + Move::W,
			index + Move::W + Move::N,
			index + Move::N,
			index + Move::N + Move::E,
		})
	{
		if (_board.radiation(neighbor) >= level)
		{
			count++;
		}
	}
	return count >= 5;
}

bool RadiationTransition::saturated(Cell index, int8_t level)
{
	for (Cell neighbor : _board.area(index, 1, 2))
	{
		if (_board.radiation(neighbor) < level - 1)
		{
			return false;
		}
	}
	return true;
}

void RadiationTransition::spread(Cell index, int8_t level, int8_t times)
{
	Randomizer<Cell> randomizer(8);
	for (Cell neighbor : {
			index + Move::E,
			index + Move::E + Move::S,
			index + Move::S,
			index + Move::S + Move::W,
			index + Move::W,
			index + Move::W + Move::N,
			index + Move::N,
			index + Move::N + Move::E,
		})
	{
		if (_board.radiation(neighbor) < level)
		{
			randomizer.push(neighbor);
		}
	}
	for (int i = 0; i < times; i++)
	{
		if (!randomizer) break;
		put(randomizer.pop(), level);
	}
}

void RadiationTransition::put(Cell index, int8_t level)
{
	DEBUG_ASSERT(level >= 0);

	// Inside _results, levels are increased by 1 so that 0 means undefined.
	uint8_t result = level + 1;
	_results[index.ix()] = std::max(_results[index.ix()], result);
}
