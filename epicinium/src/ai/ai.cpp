#include "ai.hpp"
#include "source.hpp"

#include "aihungryhippo.hpp"
#include "aiquickquack.hpp"
#include "aitutorialturtle.hpp"
#include "airampantrhino.hpp"
#include "aibrawlingbear.hpp"
#include "aibrawlingbearfree.hpp"
#include "aineuralnewt.hpp"
#include "ailibrary.hpp"


std::unique_ptr<AICommander> AI::create(const std::string& ainame,
	const Player& player, const Difficulty& difficulty,
	const std::string& ruleset, char character)
{
	return std::unique_ptr<AICommander>(
		allocate(ainame, player, difficulty, ruleset, character));
}

AICommander* AI::allocate(const std::string& ainame,
	const Player& player, const Difficulty& difficulty,
	const std::string& ruleset, char character)
{
	std::string lowered = tolower(ainame);
	if (lowered == "neuralnewt")
	{
		return new AINeuralNewt(player, difficulty, ruleset, character);
	}
	if (lowered == "quickquack")
	{
		return new AIQuickQuack(player, difficulty, ruleset, character);
	}
	if (lowered == "hungryhippo")
	{
		return new AIHungryHippo(player, difficulty, ruleset, character);
	}
	if (lowered == "tutorialturtle")
	{
		return new AITutorialTurtle(player, difficulty, ruleset, character);
	}
	if (lowered == "rampantrhino")
	{
		return new AIRampantRhino(player, difficulty, ruleset, character);
	}
	if (lowered == "brawlingbear")
	{
		return new AIBrawlingBear(player, difficulty, ruleset, character);
	}
	if (lowered == "brawlingbearfree")
	{
		return new AIBrawlingBearFree(player, difficulty, ruleset, character);
	}
	if (lowered == "dummy")
	{
		return new AIDummy(player, difficulty, ruleset, character);
	}

	LOGE << "Unknown AI '" << ainame << "'";
	DEBUG_ASSERT(false);
	return nullptr;
}

bool AI::exists(const std::string& name)
{
	std::string lowered = tolower(name);
	for (const std::string& pooled : pool())
	{
		if (lowered == tolower(pooled)) return true;
	}
	for (const std::string& pooled : hiddenPool())
	{
		if (lowered == tolower(pooled)) return true;
	}
	return false;
}

std::string AI::libraryDefaultFilename(const std::string& name)
{
	return "bin/ai" + tolower(name) + "default.so";
}

const std::vector<std::string>& AI::pool()
{
	static std::vector<std::string> pool = {
		"RampantRhino",
		"HungryHippo",
		"NeuralNewt",
	};
	return pool;
}

const std::vector<std::string>& AI::hiddenPool()
{
	static std::vector<std::string> pool = {
		"QuickQuack",
		"TutorialTurtle",
		"BrawlingBear",
		"BrawlingBearFree",
		"Dummy",
	};
	return pool;
}
