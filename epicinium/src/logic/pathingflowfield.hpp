#pragma once
#include "header.hpp"

#include "flowfield.hpp"
#include "changeset.hpp"

class Bible;
class Board;


class PathingFlowfield : public Flowfield<PathingFlowfield>
{
public:
	using Flowfield::Flowfield;

private:
	bool _air = false;

	void map(Cell /**/) {}
	void flood(Cell index);
	void reduce(Cell /**/) {}

	friend Flowfield;

public:
	void fly() { _air = true; }

	void put(Cell at, const Move& move)
	{
		Flowfield<PathingFlowfield>::put(at, move);
	}
};
