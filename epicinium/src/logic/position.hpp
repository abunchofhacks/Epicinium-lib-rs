#pragma once
#include "header.hpp"


struct Position
{
	// The board size must be strictly smaller than 128x128 because we use
	// int8_t to store _rows in Cell, so it can have values 1 to 127 inclusive.
	// We use a much smaller maximum value to help train neural networks.
	static constexpr int MAX_COLS = 32;
	static constexpr int MAX_ROWS = MAX_COLS;

	int8_t row;
	int8_t col;

	Position() :
		Position(0, 0) {}

	Position(int8_t r, int8_t c) :
		row(r),
		col(c) {}

	bool operator==(const Position& other) const
	{
		return (row == other.row && col == other.col);
	}

	bool operator!=(const Position& other) const
	{
		return !(*this == other);
	}

	bool operator<(const Position& other) const
	{
		return std::tie(row, col) < std::tie(other.row, other.col);
	}

	explicit Position(const Json::Value& json);

	friend std::ostream& operator<<(std::ostream& os, const Position& pos);
};
