#pragma once
#include "header.hpp"

class TypeNamer;
struct Change;
struct Order;
enum class Player : uint8_t;
enum class Difficulty : uint8_t;


class AILibrary
{
public:
	AILibrary() = default;
	AILibrary(const AILibrary&) = delete;
	AILibrary(AILibrary&&) = delete;
	AILibrary& operator=(const AILibrary&) = delete;
	AILibrary& operator=(AILibrary&&) = delete;
	virtual ~AILibrary() = default;

	void receiveChanges(const std::vector<Change>& changes,
		const TypeNamer& namer);
	virtual void receiveChangesAsString(const std::string& changes) = 0;

	virtual void prepareOrders() = 0;

	std::vector<Order> orders(const TypeNamer& namer);
	virtual std::string ordersAsString() = 0;

	Player player() const;
	virtual std::string playerAsString() const = 0;

	Difficulty difficulty() const;
	virtual std::string difficultyAsString() const = 0;

	virtual std::string characterstring() const = 0;

	virtual std::string displayname() const = 0;
	virtual std::string ainame() const = 0;
	virtual std::string authors() const = 0;
	virtual std::string descriptivename() const = 0;

	static bool exists(const std::string& name);
	static bool isLibraryReminder(const std::string& name);
	static bool hasFastDirective(const std::string& name);

	static void preload(const std::string& name);

	static std::shared_ptr<AILibrary> create(const std::string& name,
		const Player& player, const Difficulty& difficulty,
		const std::string& ruleset, char character);
	static AILibrary* allocate(const std::string& name,
		const Player& player, const Difficulty& difficulty,
		const std::string& ruleset, char character);

	static void setup(const char* name, int argc, const char* const argv[]);
};
