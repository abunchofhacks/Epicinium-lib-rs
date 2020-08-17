#pragma once
#include "header.hpp"

enum class Player : uint8_t;
enum class Notice : uint8_t;
class Bible;
class Board;
class PlayerInfo;
class RoundInfo;


class Challenge
{
public:
	enum Id : uint16_t
	{
		SHOWCASE,
		ELIMINATION,
		EVERYTHINGISFREE,
		TRAMPLE,
		HIGHSPEED,
		TRAMPLE2,
		INVESTMENT,
		MORALE,
	};

	Challenge(Id id) :
		_id(id)
	{}

	static Id current();

protected:
	const Id _id;

public:
	Notice check(const Bible&, const Board& board,
		const RoundInfo& rinfo, PlayerInfo& pinfo,
		std::vector<Player>& defeats);

	void score(const Bible& bible, const Board& board,
		PlayerInfo& info);
	void award(const Bible& bible, const Board& board,
		PlayerInfo& info);

	static Notice check(const Id& id, const Bible&, const Board& board,
		const RoundInfo& rinfo, PlayerInfo& pinfo,
		std::vector<Player>& defeats);

	static void score(const Id& id, const Bible& bible, const Board& board,
		PlayerInfo& info);
	static void award(const Id& id, const Bible& bible, const Board& board,
		PlayerInfo& info);
};
