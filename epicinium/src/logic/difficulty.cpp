#include "difficulty.hpp"
#include "source.hpp"

#include "parseerror.hpp"


Difficulty parseDifficulty(const std::string& str)
{
	if      (str == "none")   return Difficulty::NONE;
	else if (str == "easy")   return Difficulty::EASY;
	else if (str == "medium") return Difficulty::MEDIUM;
	else if (str == "hard")   return Difficulty::HARD;
	else throw ParseError("Unknown AI difficulty '" + str + "'");
}

const char* stringify(const Difficulty& difficulty)
{
	switch (difficulty)
	{
		case Difficulty::NONE:   return "none";
		case Difficulty::EASY:   return "easy";
		case Difficulty::MEDIUM: return "medium";
		case Difficulty::HARD:   return "hard";
	}
	return "error";
}

std::ostream& operator<<(std::ostream& os, const Difficulty& platform)
{
	return os << stringify(platform);
}
