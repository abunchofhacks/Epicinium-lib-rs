#pragma once
#include "header.hpp"

#include "descriptor.hpp"

enum class Move : uint8_t;
enum class TileType : uint8_t;
enum class UnitType : uint8_t;

class TypeNamer;


struct Order
{
public:
	enum class Type : uint8_t
	{
		NONE = 0,       // subjectless order: nothing happens ("sleep")
		MOVE,           // move to <target> cell using <moves>
		GUARD,          // guard <target> cell
		FOCUS,          // focus <target> cell
		LOCKDOWN,       // lockdown <target> cell
		SHELL,          // use short-ranged damage ability on <target> cell
		BOMBARD,        // use long-ranged damage ability on <target> cell
		BOMB,           // use melee damage ability
//		DETONATE,       // use self-destructing damage ability
//		DEPLOY,         // move into a unit, load it and fly it to <target> cell
		CAPTURE,        // capture a tile
		SHAPE,          // build a <tiletype> tile
		SETTLE,         // build and become a <tiletype> tile
		EXPAND,         // build a <tiletype> tile on <target> cell
		UPGRADE,        // build and become a <tiletype> tile
		CULTIVATE,      // build <tiletype> tiles all around
		PRODUCE,        // produce a <unittype> unit and rally it on <target> cell
		HALT,           // do nothing (this can be used to override a previous order)
	};

	static constexpr size_t TYPE_SIZE = ((size_t) Type::HALT) + 1;

	Order() :
		type(Type::NONE),
		__byte(0)
	{}

	explicit Order(Type type) :
		type(type),
		__byte(0)
	{}

	Order(Type type, const Descriptor& subject, const Descriptor& target,
			const std::vector<Move>& moves) :
		type(type),
		__byte(0),
		subject(subject),
		target(target),
		moves(moves)
	{}

	Order(Type type, const Descriptor& subject, const Descriptor& target,
			const TileType& tiletype) :
		type(type),
		tiletype(tiletype),
		subject(subject),
		target(target)
	{}

	Order(Type type, const Descriptor& subject, const Descriptor& target,
			const UnitType& unittype) :
		type(type),
		unittype(unittype),
		subject(subject),
		target(target)
	{}

	Order(Type type, const Descriptor& subject, const Descriptor& target) :
		type(type),
		__byte(0),
		subject(subject),
		target(target)
	{}

	Order(Type type, const Descriptor& subject, const TileType& tiletype) :
		type(type),
		tiletype(tiletype),
		subject(subject)
	{}

	Order(Type type, const Descriptor& subject, const UnitType& unittype) :
		type(type),
		unittype(unittype),
		subject(subject)
	{}

	Order(Type type, const Descriptor& subject) :
		type(type),
		__byte(0),
		subject(subject)
	{}

	bool finished() const
	{
		return type == Type::NONE;
	}

	Type type;
	union
	{
		TileType tiletype;
		UnitType unittype;
		// If we have neither a tiletype nor a unittype, we initialize a byte.
		uint8_t __byte;
	};
	Descriptor subject;
	Descriptor target;
	std::vector<Move> moves;

	static Order::Type parseType(const std::string& str);
	static const char* stringify(const Order::Type& type);

	explicit Order(const TypeNamer& namer, const Json::Value& json);

	friend std::ostream& operator<<(std::ostream& os, const Order::Type& type);
	friend std::ostream& operator<<(std::ostream& os, const Order& order);

	bool operator==(const Order& other) const;
	bool operator!=(const Order& other) const;

	static std::vector<Order> parseOrders(const TypeNamer& typenamer,
		const Json::Value& json);
	static std::vector<Order> parseOrders(const TypeNamer& typenamer,
		const std::string& json);
};
