/**
 * Part of Epicinium
 * developed by A Bunch of Hacks.
 *
 * Copyright (c) 2017-2020 A Bunch of Hacks
 *
 * Epicinium is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Epicinium is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Affero General Public License for more details.
 *
 * You should have received a copy of the GNU Affero General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 *
 * [authors:]
 * Sander in 't Veld (sander@abunchofhacks.coop)
 * Daan Mulder (daan@abunchofhacks.coop)
 */
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
