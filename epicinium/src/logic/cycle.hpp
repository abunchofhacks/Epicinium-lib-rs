#pragma once
#include "header.hpp"


enum class Season : uint8_t
{
	SPRING,
	SUMMER,
	AUTUMN,
	WINTER,
};

constexpr size_t SEASON_SIZE = 4;

enum class Daytime : uint8_t
{
	LATE,
	EARLY,
};

constexpr size_t DAYTIME_SIZE = 2;

enum class Phase : uint8_t
{
	GROWTH,
	RESTING,
	PLANNING,
	STAGING,
	ACTION,
	DECAY,
};

constexpr size_t PHASE_SIZE = 6;

Season  parseSeason (const std::string& str);
Daytime parseDaytime(const std::string& str);
Phase   parsePhase  (const std::string& str);

const char* stringify(const Season& season);
const char* stringify(const Daytime& daytime);
const char* stringify(const Phase& phase);

std::ostream& operator<<(std::ostream& os, const Season& value);
std::ostream& operator<<(std::ostream& os, const Daytime& value);
std::ostream& operator<<(std::ostream& os, const Phase& value);

const char* phaseDescription(const Daytime& daytime, const Phase& phase);
