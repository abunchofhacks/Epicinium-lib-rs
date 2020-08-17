#pragma once
#include "header.hpp"

#include "cycle.hpp"
#include "cell.hpp"

class Bible;
class Board;
class ChangeSet;


class MarkerTransition
{
public:
	MarkerTransition(const Bible& bible, Board& board, ChangeSet& changeset,
			const Season& season = Season::SPRING);

private:
	const Bible& _bible;
	Board& _board;
	ChangeSet& _changeset;

	const Season _season;
	int _totalchaos;

	std::vector<Cell> _randomizedFirestorm;
	std::vector<Cell> _randomizedDeath;

	std::vector<uint8_t> _results;

	void map(Cell index);
	void reduce(Cell index);

public:
	void execute();
};
