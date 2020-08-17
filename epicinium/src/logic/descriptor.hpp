#pragma once
#include "header.hpp"

#include "position.hpp"


struct Descriptor
{
public:
	enum class Type : uint8_t
	{
		NONE = 0,
		CELL,
		TILE,
		GROUND,
		AIR,
		BYPASS,
	};

	static constexpr size_t TYPE_SIZE = ((size_t) Type::BYPASS) + 1;

	static Descriptor cell(const Position& position)
	{
		return Descriptor(Type::CELL, position);
	}

	static Descriptor tile(const Position& position)
	{
		return Descriptor(Type::TILE, position);
	}

	static Descriptor ground(const Position& position)
	{
		return Descriptor(Type::GROUND, position);
	}

	static Descriptor air(const Position& position)
	{
		return Descriptor(Type::AIR, position);
	}

	static Descriptor bypass(const Position& position)
	{
		return Descriptor(Type::BYPASS, position);
	}

	Descriptor() : type(Type::NONE) {}

	Descriptor(Type type, const Position& position) :
		type(type),
		position(position)
	{}

	Type type;
	Position position;

	explicit operator bool() const
	{
		return (type != Type::NONE);
	}

	bool operator==(const Descriptor& other) const
	{
		return (type == other.type && position == other.position);
	}

	bool operator!=(const Descriptor& other) const
	{
		return !(*this == other);
	}

	bool operator<(const Descriptor& other) const
	{
		return std::tie(type, position) < std::tie(other.type, other.position);
	}

	static Descriptor::Type parseType(const std::string& str);
	static const char* stringify(const Descriptor::Type& str);

	explicit Descriptor(const Json::Value& json);

	friend std::ostream& operator<<(std::ostream& os, const Descriptor& desc);
	friend std::ostream& operator<<(std::ostream& os, const Descriptor::Type& type);
};
