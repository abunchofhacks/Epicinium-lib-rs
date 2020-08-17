#include "attacker.hpp"
#include "source.hpp"


Attacker::Attacker(const TypeNamer& namer, const Json::Value& json) :
	unittype(::parseUnitType(namer, json["unittype"].asString())),
	position(json["position"])
{}

Bombarder::Bombarder(const TypeNamer& namer, const Json::Value& json) :
	unittype(::parseUnitType(namer, json["unittype"].asString()))
{}

std::ostream& operator<<(std::ostream& os, const Attacker& attacker)
{
	return os << "{"
		"\"unittype\":\"" << attacker.unittype << "\""
		","
		"\"position\":" << attacker.position << ""
		"}";
}

std::ostream& operator<<(std::ostream& os, const Bombarder& bombarder)
{
	return os << "{"
		"\"unittype\":\"" << bombarder.unittype << "\""
		"}";
}
