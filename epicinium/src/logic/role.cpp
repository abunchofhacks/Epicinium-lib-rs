#include "role.hpp"
#include "source.hpp"

#include "parseerror.hpp"
#include "player.hpp"


Role parseRole(const std::string& str)
{
	if      (str == "none")     return Role::NONE;
	if      (str == "player")   return Role::PLAYER;
	else if (str == "observer") return Role::OBSERVER;
	else throw ParseError("Unknown role '" + str + "'");
}

const char* stringify(const Role& role)
{
	switch (role)
	{
		case Role::NONE:     return "none";
		case Role::PLAYER:   return "player";
		case Role::OBSERVER: return "observer";
	}
	return "error";
}

Player getVisionLevel(const Role& role)
{
	switch (role)
	{
		case Role::OBSERVER: return Player::OBSERVER;
		default:             return Player::BLIND;
	}
}

std::ostream& operator<<(std::ostream& os, const Role& role)
{
	return os << stringify(role);
}
