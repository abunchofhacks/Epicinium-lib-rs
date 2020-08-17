#pragma once
#include "header.hpp"


class EpochClock
{
public:
	static uint64_t seconds();
	static uint64_t milliseconds();
};

class SteadyClock
{
public:
	static uint64_t milliseconds();
};
