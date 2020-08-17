#pragma once
#include "header.hpp"

class AICommander;
enum class Player : uint8_t;
enum class Difficulty : uint8_t;


class AI
{
public:
	static AICommander* allocate(const std::string& ainame,
		const Player& player, const Difficulty& difficulty,
		const std::string& ruleset, char character);

public:
	static std::unique_ptr<AICommander> create(const std::string& ainame,
		const Player& player, const Difficulty& difficulty,
		const std::string& ruleset, char character);

	static bool exists(const std::string& name);
	static std::string libraryDefaultFilename(const std::string& name);

	static const std::vector<std::string>& pool();

private:
	static const std::vector<std::string>& hiddenPool();
};
