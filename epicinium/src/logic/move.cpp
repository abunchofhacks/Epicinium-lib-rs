#include "move.hpp"
#include "source.hpp"

#include "parseerror.hpp"


Move parseMove(const std::string& str)
{
	if      (str == "self")  return Move::X;
	else if (str == "east")  return Move::E;
	else if (str == "south") return Move::S;
	else if (str == "west")  return Move::W;
	else if (str == "north") return Move::N;
	else throw ParseError("Unknown move '" + str + "'");
}

const char* stringify(const Move& move)
{
	switch (move)
	{
		case Move::X: return "self";
		case Move::E: return "east";
		case Move::S: return "south";
		case Move::W: return "west";
		case Move::N: return "north";
	}
	return "error";
}

std::ostream& operator<<(std::ostream& os, const Move& move)
{
	return os << stringify(move);
}
