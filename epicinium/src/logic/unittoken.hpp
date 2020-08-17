#pragma once
#include "header.hpp"

#include "unittype.hpp"
#include "player.hpp"

class TypeNamer;


struct UnitToken
{
	UnitType type;
	Player owner;
	int8_t stacks;

	UnitToken() :
		type(UnitType::NONE),
		owner(Player::NONE),
		stacks(0)
	{}

	UnitToken(const TypeNamer& namer, const Json::Value& json);

	bool operator==(const UnitToken& other) const = delete;

	bool operator!=(const UnitToken& other) const
	{
		return (type  != other.type
			|| owner  != other.owner
			|| stacks != other.stacks);
	}

	explicit operator bool() const
	{
		return (type != UnitType::NONE);
	}
};

class UnitTokenWithId : public UnitToken
{
public:
	using UnitToken::UnitToken;
	UnitTokenWithId() = default;

	UnitTokenWithId(UnitToken that) :
		UnitToken(that)
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

std::ostream& operator<<(std::ostream& os, const UnitToken& token);
