#pragma once
#include "header.hpp"

#include "cell.hpp"

class Bible;
class Board;
class ChangeSet;
enum class Season : uint8_t;


class WeatherTransition
{
public:
	WeatherTransition(const Bible& bible, Board& board, ChangeSet& changeset,
			const Season& season);

private:
	const Bible& _bible;
	Board& _board;
	ChangeSet& _changeset;

	const Season _season;
	int _totalchaos;

	bool _emissionbased;
	int _emissions;

	std::vector<Cell> _randomizedAridification;

	std::vector<uint8_t> _gain;
	std::vector<uint8_t> _loss;

	void map(Cell index);
	void reduce(Cell index);

public:
	void execute();
};
