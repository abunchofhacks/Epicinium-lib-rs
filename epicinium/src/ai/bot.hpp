#pragma once
#include "header.hpp"

class AICommander;
enum class Player : uint8_t;
enum class Difficulty : uint8_t;


struct Bot
{
	const std::string slotname;
	const char character;
	std::string ainame;
	Difficulty difficulty;

	Bot(const std::string& slotname, const std::string& ainame,
		const Difficulty& difficulty);

	std::unique_ptr<AICommander> createAI(const Player& player,
		const std::string& rulesetname) const;
};
