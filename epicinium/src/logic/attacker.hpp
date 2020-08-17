#pragma once
#include "header.hpp"

#include "unittype.hpp"
#include "position.hpp"

class TypeNamer;


struct Attacker
{
public:
	UnitType unittype;
	Position position;

	explicit Attacker(const UnitType& unittype, const Position& position) :
		unittype(unittype),
		position(position)
	{}

	explicit Attacker(const TypeNamer& namer, const Json::Value& json);

	/* Uninitialized */
	Attacker() : unittype(UnitType::NONE) {}
};

struct Bombarder
{
public:
	UnitType unittype;

	explicit Bombarder(const UnitType& unittype) :
		unittype(unittype)
	{}

	explicit Bombarder(const TypeNamer& namer, const Json::Value& json);

	/* Uninitialized */
	Bombarder() : unittype(UnitType::NONE) {}
};

std::ostream& operator<<(std::ostream& os, const Attacker& attacker);
std::ostream& operator<<(std::ostream& os, const Bombarder& bombarder);
