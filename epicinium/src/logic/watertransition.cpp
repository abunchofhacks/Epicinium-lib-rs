#include "watertransition.hpp"
#include "source.hpp"

#include "aim.hpp"
#include "bible.hpp"
#include "board.hpp"
#include "changeset.hpp"
#include "cell.hpp"


WaterTransition::WaterTransition(const Bible& bible, Board& board,
		ChangeSet& changeset) :
	_bible(bible),
	_board(board),
	_changeset(changeset),
	_oceans(bible, board),
	_gain(_board.end().ix(), 0),
	_loss(_board.end().ix(), 0)
{
	_oceans.execute();
}

void WaterTransition::execute()
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

void WaterTransition::map(Cell index)
{
	int range = _bible.humGenGainRange();
	if (range < 0) return;

	if (_bible.tileWater(_board.tile(index).type))
	{
		if (_oceans.ocean(index))
		{
			for (Cell to : _board.area(index, 0, range))
			{
				size_t dist = Aim(index.pos(), to.pos()).sumofsquares();
				put(to, _bible.humGenOceanGain(dist));
			}
		}
		else
		{
			for (Cell to : _board.area(index, 0, range))
			{
				size_t dist = Aim(index.pos(), to.pos()).sumofsquares();
				put(to, _bible.humGenLakeGain(dist));
			}
		}
	}

	if (_bible.tileMountain(_board.tile(index).type))
	{
		for (Cell to : _board.area(index, 0, range))
		{
			size_t dist = Aim(index.pos(), to.pos()).sumofsquares();
			put(to, _bible.humGenMountainGain(dist));
		}
	}

	if (_bible.tileDesert(_board.tile(index).type))
	{
		for (Cell to : _board.area(index, 0, range))
		{
			size_t dist = Aim(index.pos(), to.pos()).sumofsquares();
			put(to, _bible.humGenDesertGain(dist));
		}
	}
}

void WaterTransition::put(Cell index, int8_t gainorloss)
{
	if (gainorloss > 0)
	{
		uint8_t gain = gainorloss;
		_gain[index.ix()] = std::max(_gain[index.ix()], gain);
	}
	else if (gainorloss < 0)
	{
		uint8_t loss = -gainorloss;
		_loss[index.ix()] = std::max(_loss[index.ix()], loss);
	}
}

void WaterTransition::reduce(Cell index)
{
	// Calculate the humidity change.
	uint8_t gain = _gain[index.ix()];
	uint8_t loss = _loss[index.ix()];

	int8_t freshwater;
	if (-loss <= _bible.humGenDesertGain(0)) freshwater = -loss;
	else if (gain >= _bible.humGenMountainGain(0)) freshwater = gain;
	else freshwater = gain - loss;

	int target = (int) _bible.humGenDefault() + freshwater;
	int8_t humidity = std::max((int) _bible.humidityMin(),
		std::min(target, (int) _bible.humidityMax()));

	int8_t diff = humidity - _board.humidity(index);
	if (diff)
	{
		Change change(Change::Type::HUMIDITY, Descriptor::cell(index.pos()));
		change.xHumidity(diff);
		_board.enact(change);
		_changeset.push(change, _board.vision(index));
	}
}
