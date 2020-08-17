#pragma once
#include "header.hpp"


enum class Move : uint8_t
{
	X, E, S, W, N
};

static constexpr size_t MOVE_SIZE = ((size_t) Move::N) + 1;

inline Move flip(const Move& move)
{
	switch (move)
	{
		case Move::E: return Move::W;
		case Move::S: return Move::N;
		case Move::W: return Move::E;
		case Move::N: return Move::S;
		default: return Move::X;
	}
}

Move parseMove(const std::string& str);
const char* stringify(const Move& move);

std::ostream& operator<<(std::ostream& os, const Move& move);
