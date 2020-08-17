#pragma once
#include "header.hpp"

#include "change.hpp"
#include "vision.hpp"

enum class Player : uint8_t;
class TypeNamer;


class ChangeSet
{
private:
	std::vector<std::pair<Change, Vision>> _data;

public:
	ChangeSet() = default;

	ChangeSet(const TypeNamer& namer, const Json::Value& json);

	void push(const Change& change, const Vision& vision)
	{
		_data.emplace_back(std::make_pair(change, vision));
	}

	std::vector<Change> get(const Player& player) const
	{
		std::vector<Change> results;
		for (const auto& kv : _data)
		{
			if (kv.second.contains(player))
			{
				results.push_back(kv.first);
			}
		}
		return results;
	}

	friend std::ostream& operator<<(std::ostream& os,
		const ChangeSet& changeset);

	static bool equal(const TypeNamer& namer,
		const ChangeSet& a, const ChangeSet& b);

	bool any() const
	{
		return (!_data.empty());
	}

	explicit operator bool() const
	{
		return any();
	}
};
