#include "aitutorialturtle.hpp"
#include "source.hpp"

#include "difficulty.hpp"


std::string AITutorialTurtle::ainame() const
{
	return "TutorialTurtle";
}

std::string AITutorialTurtle::authors() const
{
	return "Sander in 't Veld";
}

int AITutorialTurtle::maxOrders()
{
	switch (_difficulty)
	{
		case Difficulty::NONE: return 0;
		case Difficulty::EASY: return 2;
		case Difficulty::MEDIUM: return 5;
		case Difficulty::HARD: return 5;
	}
	return 0;
}

int AITutorialTurtle::maxMilitaryOrders()
{
	switch (_difficulty)
	{
		case Difficulty::NONE: return 0;
		case Difficulty::EASY: return 1;
		case Difficulty::MEDIUM: return 3;
		case Difficulty::HARD: return 4;
	}
	return 0;
}

int AITutorialTurtle::maxMilitaryUnits()
{
	switch (_difficulty)
	{
		case Difficulty::NONE: return 0;
		case Difficulty::EASY: return 1;
		case Difficulty::MEDIUM: return 6;
		case Difficulty::HARD: return 10;
	}
	return 0;
}

int AITutorialTurtle::maxDefenseUnits()
{
	// The tutorialturtle never declares attackers.
	return 1000;
}

int AITutorialTurtle::maxCaptures()
{
	// The tutorialturtle never captures.
	return 0;
}

int AITutorialTurtle::maxBombardments()
{
	switch (_difficulty)
	{
		case Difficulty::NONE: return 0;
		case Difficulty::EASY: return 0;
		case Difficulty::MEDIUM: return 1;
		case Difficulty::HARD: return 1;
	}
	return 0;
}
