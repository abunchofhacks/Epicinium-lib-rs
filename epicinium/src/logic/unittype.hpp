#pragma once
#include "header.hpp"

class TypeNamer;


enum class UnitType : uint8_t
{
	NONE = 0,
};

static constexpr size_t UNITTYPE_SIZE = 32;

UnitType parseUnitType(const TypeNamer& namer, const std::string& str);

std::ostream& operator<<(std::ostream& os, const UnitType& type);
