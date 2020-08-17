#pragma once
#include "header.hpp"

#include "challenge.hpp"
#include "player.hpp"
#include "bot.hpp"


class AIChallenge : public Challenge
{
public:
	enum class Brief : uint8_t
	{
		GREETING,
		DESCRIPTION,
		OBJECTIVE,
		FIRST_STAR,
		SECOND_STAR,
		THIRD_STAR,
		SENDOFF,
	};
	static constexpr size_t BRIEF_SIZE = ((size_t) Brief::SENDOFF) + 1;
	static const char* stringify(const Brief& brief);

	using Challenge::Challenge;

	AIChallenge(const Challenge& that) : Challenge(that) {}
	AIChallenge(Challenge&& that) : Challenge(that) {}
	AIChallenge& operator=(const Challenge&) = delete;
	AIChallenge& operator=(Challenge&&) = delete;

public:
	std::string getKey();
	std::vector<Player> getPlayers();
	std::vector<Bot> getBots();
	std::string getMapName();
	std::string getRulesetName();
	std::string getDisplayName();
	std::string getPanelPictureName();
	std::string getDiscordImageKey();
	Json::Value getMissionBriefing();

	static const char* getKey(const Challenge::Id& id);
	static size_t getNumBots(const Challenge::Id& id);
	static const char* getBotName(const Challenge::Id& id);
	static Difficulty getBotDifficulty(const Challenge::Id& id);
	static const char* getMapName(const Challenge::Id& id);
	static const char* getRulesetName(const Challenge::Id& id);
	static const char* getDisplayName(const Challenge::Id& id);
	static const char* getPanelPictureName(const Challenge::Id& id);
	static const char* getDiscordImageKey(const Challenge::Id& id);
	static const char* getBrief(const Challenge::Id& id, const Brief& brief);
};
