#pragma once
#include "header.hpp"

#include "tiletype.hpp"
#include "player.hpp"

class TypeNamer;


struct TileToken
{
	TileType type;
	Player owner;
	int8_t stacks;
	int8_t power;

	TileToken() :
		type(TileType::NONE),
		owner(Player::NONE),
		stacks(0),
		power(0)
	{}

	TileToken(const TypeNamer& namer, const Json::Value& json);

	bool operator==(const TileToken& other) const = delete;

	bool operator!=(const TileToken& other) const
	{
		return (type  != other.type
			|| owner  != other.owner
			|| stacks != other.stacks
			|| power  != other.power);
	}

	explicit operator bool() const
	{
		return (type != TileType::NONE);
	}
};

class TileTokenWithId : public TileToken
{
public:
	using TileToken::TileToken;
	TileTokenWithId() = default;

	TileTokenWithId(TileToken that) :
		TileToken(that)
	{}

private:
	uint32_t _id = 0;

public:
	void assignId(uint32_t assigned)
	{
		_id = assigned;
	}

	void resetId()
	{
		_id = 0;
	}

	uint32_t id() const
	{
		return _id;
	}
};

std::ostream& operator<<(std::ostream& os, const TileToken& token);
