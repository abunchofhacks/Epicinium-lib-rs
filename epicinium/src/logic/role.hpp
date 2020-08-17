#pragma once
#include "header.hpp"


enum class Player : uint8_t;

enum class Role : uint8_t
{
	NONE = 0,
	PLAYER,
	OBSERVER,
};

Role parseRole(const std::string& str);
const char* stringify(const Role& role);

Player getVisionLevel(const Role& role);

std::ostream& operator<<(std::ostream& os, const Role& role);
