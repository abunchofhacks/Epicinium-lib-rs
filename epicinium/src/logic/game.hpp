#pragma once
#include "header.hpp"

class TypeNamer;
struct Change;
struct Order;


class Game
{
protected:
	Game() = default;

public:
	Game(const Game&) = delete;
	Game(Game&&) = delete;
	Game& operator=(const Game&) = delete;
	Game& operator=(Game&&) = delete;
	virtual ~Game() = default;

	virtual void load() = 0;
	virtual void update() = 0;

	virtual bool online() const = 0;
	virtual bool test() const = 0;

	virtual float planningTimeTotal() const = 0;
	virtual float planningTimeSpent() const = 0;
	virtual bool haveSentOrders() const = 0;

	virtual void sendOrders() = 0;

	virtual void receiveChanges(const Json::Value& /**/) {}
	virtual void sync(uint32_t /*time*/) {}
	virtual void setAnimation(bool /*animate*/) {}

	virtual void chat(const std::string& message,
		const std::string& target) = 0;

	virtual void attemptQuit() = 0;
	virtual void confirmQuit() = 0;

};
