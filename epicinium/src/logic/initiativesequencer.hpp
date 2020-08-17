#pragma once
#include "header.hpp"


class InitiativeSequencer
{
public:
	static constexpr uint8_t MAX_NUM = 8;

	InitiativeSequencer(uint8_t number_of_players);

private:
	uint8_t _num;

public:
	// E.g. getPlayerIndex(round, 0) determines which player goes first.
	uint8_t getPlayerIndex(uint32_t round, uint8_t offset);
};
