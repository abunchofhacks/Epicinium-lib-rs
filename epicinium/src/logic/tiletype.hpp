#pragma once
#include "header.hpp"

class TypeNamer;


enum class TileType : uint8_t
{
	NONE = 0,
};

static constexpr size_t TILETYPE_SIZE = 32;

TileType parseTileType(const TypeNamer& namer, const std::string& str);

std::ostream& operator<<(std::ostream& os, const TileType& type);
