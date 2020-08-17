#pragma once
#include "header.hpp"

#include "tiletoken.hpp"
#include "cycle.hpp"

class Bible;
class Board;
class ChangeSet;
class Cell;


class TransformTransition
{
public:
	TransformTransition(const Bible& bible, Board& board, ChangeSet& changeset,
			const Season& season);

private:
	const Bible& _bible;
	Board& _board;
	ChangeSet& _changeset;

	const Season _season;
	const bool _spring;
	int _totalchaos;

	std::vector<TileToken> _results;

	void map(Cell index);
	void reduce(Cell index);

public:
	void execute();
};
