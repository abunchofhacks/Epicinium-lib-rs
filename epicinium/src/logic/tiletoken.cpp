#include "tiletoken.hpp"
#include "source.hpp"


TileToken::TileToken(const TypeNamer& namer, const Json::Value& json) :
	TileToken()
{
	if (!json["type"].isNull())
	{
		type = parseTileType(namer, json["type"].asString());
	}
	if (!json["owner"].isNull())
	{
		owner = parsePlayer(json["owner"].asString());
	}
	if (!json["stacks"].isNull())
	{
		stacks = json["stacks"].asInt();
	}
	if (!json["power"].isNull())
	{
		power = json["power"].asInt();
	}
}

std::ostream& operator<<(std::ostream& os, const TileToken& token)
{
	os << "{";
	bool empty = true;
	if (token.type != TileType::NONE)
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
		os << "\"stacks\":" << ((int) token.stacks);
	}
	if (token.power != 0)
	{
		if (empty) empty = false;
		else os << ",";
		os << "\"power\":" << ((int) token.power);
	}
	return os << "}";
}
