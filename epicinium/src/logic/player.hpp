#pragma once
#include "header.hpp"


enum class Player : uint8_t
{
	// No player.
	NONE = 0,
	// Player colors.
	RED,
	BLUE,
	YELLOW,
	TEAL,
	BLACK,
	PINK,
	INDIGO,
	PURPLE,
	// Non-player vision types used by the Automaton.
	BLIND,
	OBSERVER,
	// Non-player vision type used by the Board/Level to keep track of its
	// owner's vision.
	SELF,
};

constexpr size_t PLAYER_MAX = 8;
constexpr size_t PLAYER_SIZE = ((size_t) Player::SELF) + 1;

constexpr bool isPlayer(const Player& player)
{
	return (player != Player::NONE && ((size_t) player) <= PLAYER_MAX);
}

std::vector<Player> getPlayers(size_t n);
Player parsePlayer(const std::string& str);
const char* stringify(const Player& player);

std::ostream& operator<<(std::ostream& os, const Player& player);
