#include "bot.hpp"
#include "source.hpp"

#include "difficulty.hpp"
#include "ai.hpp"
#include "aicommander.hpp"


Bot::Bot(const std::string& s, const std::string& a, const Difficulty& d) :
	slotname(s),
	character(s[1]),
	ainame(a),
	difficulty(d)
{}

std::unique_ptr<AICommander> Bot::createAI(const Player& player,
	const std::string& rulesetname) const
{
	return AI::create(ainame, player, difficulty, rulesetname, character);
}
