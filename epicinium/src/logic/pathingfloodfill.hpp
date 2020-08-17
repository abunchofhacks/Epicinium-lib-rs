#pragma once
#include "header.hpp"

#include "floodfill.hpp"
#include "changeset.hpp"

class Bible;
class Board;


// PathingFloodfillImplementation has 3 realizations.
template <class This>
class PathingFI : public Floodfill<PathingFI<This>>
{
public:
	using Floodfill<PathingFI<This>>::Floodfill;

protected:
	bool _air = false;

	void map(Cell index)
	{
		static_cast<This*>(this)->map(index);
	}
	void flood(Cell index);
	void reduce(Cell /**/) {}

	friend Floodfill<PathingFI<This>>;
	using  Floodfill<PathingFI<This>>::_bible;
	using  Floodfill<PathingFI<This>>::_board;
	using  Floodfill<PathingFI<This>>::put;
	using  Floodfill<PathingFI<This>>::get;

public:
	void walk() { _air = false; }
	void fly() { _air = true; }

	Move step(Cell from) const;
	uint16_t steps(Cell index) const;
	bool reached(Cell index) const;
};

class PathingFloodfill : public PathingFI<PathingFloodfill>
{
public:
	using PathingFI::PathingFI;

private:
	friend PathingFI;

	void map(Cell /**/) {}

public:
	void put(Cell at)
	{
		PathingFI<PathingFloodfill>::put(at);
	}
};

class TileFloodfill : public PathingFI<TileFloodfill>
{
public:
	using PathingFI::PathingFI;

private:
	std::vector<Player> _players;
	std::vector<TileType> _types;
	bool _excludePlayers = true;
	bool _excludeTypes = true;
	bool _excludeOccupied = false;

	friend PathingFI;

	void map(Cell index);

public:
	void include(std::vector<Player> players);
	void exclude(std::vector<Player> players);
	void include(std::vector<TileType> types);
	void exclude(std::vector<TileType> types);
	void excludeOccupied(bool exclude = true);
};

class UnitFloodfill : public PathingFI<UnitFloodfill>
{
public:
	using PathingFI::PathingFI;

private:
	std::vector<Player> _players;
	std::vector<UnitType> _types;
	bool _excludePlayers = true;
	bool _excludeTypes = true;

	friend PathingFI;

	void map(Cell index);

public:
	void include(std::vector<Player> players);
	void exclude(std::vector<Player> players);
	void include(std::vector<UnitType> types);
	void exclude(std::vector<UnitType> types);
};