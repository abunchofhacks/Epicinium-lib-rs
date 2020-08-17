#include "cycle.hpp"
#include "source.hpp"

#include "parseerror.hpp"


Season parseSeason(const std::string& str)
{
	if      (str == "spring") return Season::SPRING;
	else if (str == "summer") return Season::SUMMER;
	else if (str == "autumn") return Season::AUTUMN;
	else if (str == "winter") return Season::WINTER;
	else throw ParseError("Unknown season '" + str + "'");
}

Daytime parseDaytime(const std::string& str)
{
	if      (str == "early") return Daytime::EARLY;
	else if (str == "late")  return Daytime::LATE;
	else throw ParseError("Unknown daytime '" + str + "'");
}

Phase parsePhase(const std::string& str)
{
	if      (str == "growth")   return Phase::GROWTH;
	else if (str == "resting")  return Phase::RESTING;
	else if (str == "planning") return Phase::PLANNING;
	else if (str == "staging")  return Phase::STAGING;
	else if (str == "action")   return Phase::ACTION;
	else if (str == "decay")    return Phase::DECAY;
	else throw ParseError("Unknown phase '" + str + "'");
}

const char* stringify(const Season& value)
{
	switch (value)
	{
		case Season::SPRING: return "spring";
		case Season::SUMMER: return "summer";
		case Season::AUTUMN: return "autumn";
		case Season::WINTER: return "winter";
	}
	return "error";
}

const char* stringify(const Daytime& value)
{
	switch (value)
	{
		case Daytime::EARLY: return "early";
		case Daytime::LATE:  return "late";
	}
	return "error";
}

const char* stringify(const Phase& value)
{
	switch (value)
	{
		case Phase::GROWTH:   return "growth";
		case Phase::RESTING:  return "resting";
		case Phase::PLANNING: return "planning";
		case Phase::STAGING:  return "staging";
		case Phase::ACTION:   return "action";
		case Phase::DECAY:    return "decay";
	}
	return "error";
}

std::ostream& operator<<(std::ostream& os, const Season& value)  { return os << stringify(value); }
std::ostream& operator<<(std::ostream& os, const Daytime& value) { return os << stringify(value); }
std::ostream& operator<<(std::ostream& os, const Phase& value)   { return os << stringify(value); }

const char* phaseDescription(const Daytime& daytime, const Phase& phase)
{
	switch (phase)
	{
		case Phase::GROWTH:
		{
			switch (daytime)
			{
				case Daytime::LATE:
				{
					return "In the Weather phase,"
					" the season changes and crops can grow."
					" In Spring, trees can grow."
					" In Autumn, global warming worsens."
					;
				}
				break;

				case Daytime::EARLY:
				{
					return "In the Night phase,"
					" building tiles gain power depending on their surroundings"
					" and generate income."
					;
				}
				break;
			}
		}
		break;

		case Phase::PLANNING:
		{
			return "In the Planning phase,"
			" players decide which orders to give to their units and tiles."
			" Orders are executed in the Action phase."
			;
		}
		break;

		case Phase::ACTION:
		{
			return "In the Action phase,"
			" players take turns automatically executing their orders."
			;
		}
		break;

		case Phase::DECAY:
		{
			return "In the Decay phase,"
			" any Frostbite, Firestorm or Gas present on the map deals damage."
			" Gas spreads out or dissipates."
			;
		}
		break;

		case Phase::RESTING:
		case Phase::STAGING:
		break;
	}

	return "";
}

