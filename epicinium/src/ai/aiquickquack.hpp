#pragma once
#include "header.hpp"

#include "aicommander.hpp"
#include "cell.hpp"

enum class TileType : uint8_t;


class AIQuickQuack : public AICommander
{
public:
	AIQuickQuack(const Player& player, const Difficulty& difficulty,
		const std::string& rulesetname, char character);
	AIQuickQuack(const AIQuickQuack&) = delete;
	AIQuickQuack(AIQuickQuack&&) = delete;
	AIQuickQuack& operator=(const AIQuickQuack&) = delete;
	AIQuickQuack& operator=(AIQuickQuack&&) = delete;
	virtual ~AIQuickQuack() = default;

private:
	std::vector<TileType> _citytypes;

	bool cityOccupied(Cell index) const;

protected:
	virtual std::string ainame() const override;
	virtual std::string authors() const override;

	virtual void process() override;
};
