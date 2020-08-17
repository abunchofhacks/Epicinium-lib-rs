#include "unittoken.hpp"
#include "source.hpp"


UnitToken::UnitToken(const TypeNamer& namer, const Json::Value& json) :
	UnitToken()
{
	if (!json["type"].isNull())
	{
		type = parseUnitType(namer, json["type"].asString());
	}
	if (!json["owner"].isNull())
	{
		owner = parsePlayer(json["owner"].asString());
	}
	if (!json["stacks"].isNull())
	{
		stacks = json["stacks"].asInt();
	}
}

std::ostream& operator<<(std::ostream& os, const UnitToken& token)
{
	os << "{";
	bool empty = true;
	if (token.type != UnitType::NONE)
	{
		if (empty) empty = false;
		else os << ",";
		os << "\"type\":\"" << token.type << "\"";
	}
	if (token.owner != Player::NONE)
	{
		if (empty) empty = false;
		else os << ",";
		os << "\"owner\":\"" << token.owner << "\"";
	}
	if (token.stacks != 0)
	{
		if (empty) empty = false;
		else os << ",";
		os << "\"stacks\":" << ((int) token.stacks) << "";
	}
	return os << "}";
}
