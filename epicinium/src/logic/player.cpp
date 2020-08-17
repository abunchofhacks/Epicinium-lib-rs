#include "player.hpp"
#include "source.hpp"

#include "parseerror.hpp"


std::vector<Player> getPlayers(size_t n)
{
	if (n > PLAYER_MAX) throw std::runtime_error("More than eight players not supported");

	std::vector<Player> players;
	for (size_t i = 1; i <= n; i++)
	{
		players.push_back(Player(i));
	}
	return players;
}

Player parsePlayer(const std::string& str)
{
	if      (str == "none")     return Player::NONE;
	else if (str == "nature")   return Player::NONE;
	else if (str == "red")      return Player::RED;
	else if (str == "blue")     return Player::BLUE;
	else if (str == "teal")     return Player::TEAL;
	else if (str == "yellow")   return Player::YELLOW;
	else if (str == "black")    return Player::BLACK;
	else if (str == "pink")     return Player::PINK;
	else if (str == "indigo")   return Player::INDIGO;
	else if (str == "purple")   return Player::PURPLE;
	else if (str == "alice")    return Player::RED;
	else if (str == "bob")      return Player::BLUE;
	else if (str == "carol")    return Player::TEAL;
	else if (str == "dave")     return Player::YELLOW;
	else if (str == "emma")     return Player::PINK;
	else if (str == "frank")    return Player::BLACK;
	else if (str == "blind")    return Player::BLIND;
	else if (str == "observer") return Player::OBSERVER;
	else if (str == "self")     return Player::SELF;
	else throw ParseError("Unknown player '" + str + "'");
}

const char* stringify(const Player& player)
{
	switch (player)
	{
		case Player::NONE:     return "none";
		case Player::RED:      return "red";
		case Player::BLUE:     return "blue";
		case Player::YELLOW:   return "yellow";
		case Player::TEAL:     return "teal";
		case Player::BLACK:    return "black";
		case Player::PINK:     return "pink";
		case Player::INDIGO:   return "indigo";
		case Player::PURPLE:   return "purple";
		case Player::BLIND:    return "blind";
		case Player::OBSERVER: return "observer";
		case Player::SELF:     return "self";
	}
	return "error";
}

std::ostream& operator<<(std::ostream& os, const Player& player)
{
	return os << stringify(player);
}
