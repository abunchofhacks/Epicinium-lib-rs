#pragma once
#include "header.hpp"


enum class Difficulty : uint8_t
{
	NONE = 0,
	EASY,
	MEDIUM,
	HARD,
};

Difficulty parseDifficulty(const std::string& str);
const char* stringify(const Difficulty& difficulty);

std::ostream& operator<<(std::ostream& os, const Difficulty& platform);
