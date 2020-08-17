#include "vision.hpp"
#include "source.hpp"

Vision::Vision(const Json::Value& json)
{
	for (const auto& player : json)
	{
		add(parsePlayer(player.asString()));
	}
}

std::ostream& operator<<(std::ostream& os, const Vision& vision)
{
	os << "[";
	bool empty = true;
	for (const Player& player : vision)
	{
		if (empty) empty = false;
		else os << ",";
		os << "\"" << player << "\"";
	}
	return os << "]";
}
