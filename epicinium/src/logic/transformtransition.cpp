#include "transformtransition.hpp"
#include "source.hpp"

#include "bible.hpp"
#include "board.hpp"
#include "changeset.hpp"
#include "cell.hpp"


TransformTransition::TransformTransition(const Bible& bible, Board& board,
	ChangeSet& changeset, const Season& season) :
	_bible(bible),
	_board(board),
	_changeset(changeset),
	_season(season),
	_spring(_season == Season::SPRING),
	_totalchaos(0),
	_results(_board.end().ix())
{
	for (Cell index : _board)
	{
		_totalchaos += _board.chaos(index);
	}
}

void TransformTransition::execute()
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

void TransformTransition::map(Cell index)
{
	const TileToken& tiletoken = _board.tile(index);
	const TileType tiletype = tiletoken.type;
	int temp = _board.temperature(index);
	int hum = _board.humidity(index);
	int chaos = _board.chaos(index);
	if (_bible.quantitativeChaos() && _board.mass() > 0)
	{
		chaos = _totalchaos / _board.mass();
	}

	bool growth;
	bool degradation;
	bool desertification;

	if (_bible.counterBasedWeather())
	{
		growth = (hum >= _bible.humidityMinWet(_season)
			&& !_board.snow(index));
	}
	else
	{
		growth = hum >= _bible.humidityMinWet(_season)
			&& temp >= _bible.temperatureMinComfortable(_season)
			&& temp <= _bible.temperatureMaxComfortable(_season);
	}

	degradation = (hum <= _bible.humidityMaxDegradation(_season)
		&& chaos >= _bible.chaosMinDegradation(_season));
	desertification = (hum <= _bible.humidityMaxDesertification(_season)
		&& chaos >= _bible.chaosMinDesertification(_season));

	const TileType regrowntype = _bible.tileRegrown(tiletype);
	const TileType degradedtype = _bible.tileDegraded(tiletype);
	const TileType desertifiedtype = _bible.tileDesertified(tiletype);

	// In spring, forests can grow if the environment nurtures plant growth.
	if (growth && regrowntype == tiletype
		&& (_spring || !_bible.tileRegrowOnlyInSpring(tiletype)))
	{
		// Forests grow up to 2 stacks.
		int max = _bible.tileStacksMax(tiletype);
		if (tiletoken.stacks < max)
		{
			// Probability 50%.
			int divisor = _bible.tileRegrowthProbabilityDivisor(tiletype);
			if (divisor >= 0 && (divisor <= 1 || (rand() % divisor) == 0))
			{
				TileToken newtoken = tiletoken;
				int amount = _bible.tileRegrowthAmount(tiletype);
				newtoken.stacks = std::min(tiletoken.stacks + amount, max);
				_results[index.ix()] = newtoken;
			}
		}
	}
	// If the environment nurtures plant growth, dirt can regrow into grass.
	else if (growth && regrowntype != TileType::NONE
		&& (_spring || !_bible.tileRegrowOnlyInSpring(tiletype)))
	{
		// Probability 50%.
		int divisor = _bible.tileRegrowthProbabilityDivisor(tiletype);
		if (divisor >= 0 && (divisor <= 1 || (rand() % divisor) == 0))
		{
			TileToken newtoken;
			newtoken.type = regrowntype;
			if (_bible.tileOwnable(regrowntype))
			{
				newtoken.owner = tiletoken.owner;
			}
			newtoken.stacks = _bible.tileRegrowthAmount(tiletype);
			_results[index.ix()] = newtoken;
		}
	}
	else if (degradation && degradedtype != TileType::NONE)
	{
		TileToken newtoken;
		newtoken.type = degradedtype;
		if (_bible.tileOwnable(degradedtype))
		{
			newtoken.owner = tiletoken.owner;
		}
		_results[index.ix()] = newtoken;
	}
	else if (desertification && desertifiedtype != TileType::NONE)
	{
		TileToken newtoken;
		newtoken.type = desertifiedtype;
		if (_bible.tileOwnable(desertifiedtype))
		{
			newtoken.owner = tiletoken.owner;
		}
		_results[index.ix()] = newtoken;
	}
}

void TransformTransition::reduce(Cell index)
{
	const TileToken& token = _results[index.ix()];

	if (token)
	{
		Change change(Change::Type::TRANSFORMED,
			Descriptor::tile(index.pos()),
			token);
		_board.enact(change);
		_changeset.push(change, _board.vision(index));
	}
}
