#include "descriptor.hpp"
#include "source.hpp"

#include "parseerror.hpp"


Descriptor::Type Descriptor::parseType(const std::string& str)
{
	if      (str == "cell")   return Descriptor::Type::CELL;
	else if (str == "tile")   return Descriptor::Type::TILE;
	else if (str == "ground") return Descriptor::Type::GROUND;
	else if (str == "air")    return Descriptor::Type::AIR;
	else if (str == "bypass") return Descriptor::Type::BYPASS;
	else if (str == "none")   return Descriptor::Type::NONE;
	else throw ParseError("Unknown descriptor type '" + str + "'");
}

const char* Descriptor::stringify(const Descriptor::Type& type)
{
	switch (type)
	{
		case Descriptor::Type::CELL:   return "cell";
		case Descriptor::Type::TILE:   return "tile";
		case Descriptor::Type::GROUND: return "ground";
		case Descriptor::Type::AIR:    return "air";
		case Descriptor::Type::BYPASS: return "bypass";
		case Descriptor::Type::NONE:   return "none";
	}
	return "error";
}

Descriptor::Descriptor(const Json::Value& json) :
	type(parseType(json["type"].asString())),
	position(json)
{}

std::ostream& operator<<(std::ostream& os, const Descriptor& desc)
{
	return os << "{"
		"\"type\":\"" << Descriptor::stringify(desc.type) << "\""
		","
		"\"row\":" << ((int) desc.position.row) << ""
		","
		"\"col\":" << ((int) desc.position.col) << ""
		"}";
}

std::ostream& operator<<(std::ostream& os, const Descriptor::Type& type)
{
	return os << Descriptor::stringify(type);
}
