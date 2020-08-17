#include "unittype.hpp"
#include "source.hpp"

#include "parseerror.hpp"
#include "typenamer.hpp"


UnitType parseUnitType(const TypeNamer& namer, const std::string& str)
{
	UnitType type = namer.unittype(str.c_str());
	if (type == UnitType::NONE && str != "none")
	{
		throw ParseError("Unknown unittype '" + str + "'");
	}
	return type;
}

std::ostream& operator<<(std::ostream& os, const UnitType& type)
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
