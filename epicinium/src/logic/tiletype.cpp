#include "tiletype.hpp"
#include "source.hpp"

#include "parseerror.hpp"
#include "typenamer.hpp"


TileType parseTileType(const TypeNamer& namer, const std::string& str)
{
	TileType type = namer.tiletype(str.c_str());
	if (type == TileType::NONE && str != "none")
	{
		throw ParseError("Unknown tiletype '" + str + "'");
	}
	return type;
}

std::ostream& operator<<(std::ostream& os, const TileType& type)
{
	TypeNamer* namer = (TypeNamer*) os.pword(TypeEncoder::stream_flag_index);
	DEBUG_ASSERT(namer && "Missing TypeEncoder.");
	if (namer)
	{
		return os << namer->typeword(type);
	}
	else
	{
		return os << (int) type;
	}
}
