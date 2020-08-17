#pragma once
#include "header.hpp"

#include <map>

#include "order.hpp"

enum class Player : uint8_t;


class PlayerInfo
{
public:
	explicit PlayerInfo(size_t playercount) :
		_playercount(playercount)
	{}

	~PlayerInfo() = default;
	PlayerInfo(const PlayerInfo&) = delete;
	PlayerInfo(PlayerInfo&&) = delete;

	PlayerInfo& operator=(const PlayerInfo&) = delete;
	PlayerInfo& operator=(PlayerInfo&&) = delete;

	size_t _playercount;
	std::vector<Player> _players;
	std::map<Player, int16_t> _money;
	std::map<Player, int8_t> _initiative;
	std::map<Player, std::vector<Order>> _orderlists;
	std::map<Player, bool> _citybound;
	std::map<Player, bool> _defeated;
	std::map<Player, int> _score;
	std::map<Player, int> _award;
	std::vector<Player> _visionaries;
};
