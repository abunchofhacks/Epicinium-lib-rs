#pragma once
#include "header.hpp"

#include "implodingptr.hpp"

class Game;
class Challenge;
enum class Player : uint8_t;
enum class Role : uint8_t;


class GameOwner
{
protected:
	GameOwner() = default;

public:
	GameOwner(const GameOwner& /**/) = delete;
	GameOwner(GameOwner&& /**/) = delete;
	GameOwner& operator=(const GameOwner& /**/) = delete;
	GameOwner& operator=(GameOwner&& /**/) = delete;
	virtual ~GameOwner() = default;

	virtual std::weak_ptr<Game> startGame(imploding_ptr<Game> game) = 0;
	virtual std::weak_ptr<Game> startChallenge(const Challenge& challenge) = 0;
	virtual std::weak_ptr<Game> startGame(
		const Player& player, const std::string& rulesetname,
		uint32_t planningTime) = 0;
	virtual std::weak_ptr<Game> startTutorial(
		const Player& player, const std::string& rulesetname,
		uint32_t planningTime) = 0;
	virtual std::weak_ptr<Game> startReplay(
		const Role& role, const std::string& rulesetname,
		uint32_t planningTime) = 0;
	virtual std::weak_ptr<Game> startDiorama() = 0;

	virtual void stopGame() = 0;
};
