#pragma once
#include "header.hpp"

#include "position.hpp"
#include "move.hpp"


struct Aim
{
	int8_t rowdiff;
	int8_t coldiff;

	bool operator==(const Aim& other) const
	{
		return rowdiff == other.rowdiff && coldiff == other.coldiff;
	}

	bool operator!=(const Aim& other) const
	{
		return !(*this == other);
	}

	Aim(int8_t r, int8_t c) : rowdiff(r), coldiff(c) {}

	explicit Aim(const Move& move) :
		Aim((move == Move::S) - (move == Move::N),
			(move == Move::E) - (move == Move::W))
	{}

	explicit Aim(const Position& from, const Position& to) :
		Aim(to.row - from.row, to.col - from.col)
	{}

	int length()
	{
		return abs((int) rowdiff) + abs((int) coldiff);
	}

	int sumofsquares()
	{
		return rowdiff * rowdiff + coldiff * coldiff;
	}

	Move direction() const;

	std::vector<Move> deconstruct() const;

	explicit Aim(const Json::Value& json);

	friend std::ostream& operator<<(std::ostream& os, const Aim& aim);
};

inline Position operator+(Position pos, const Aim& aim)
{
	pos.row += aim.rowdiff;
	pos.col += aim.coldiff;
	return pos;
}
