#pragma once
#include "header.hpp"

enum class Season : uint8_t;
enum class Daytime : uint8_t;
enum class Phase : uint8_t;


class RoundInfo
{
public:
	explicit RoundInfo();

	~RoundInfo() = default;
	RoundInfo(const RoundInfo&) = delete;
	RoundInfo(RoundInfo&&) = delete;

	RoundInfo& operator=(const RoundInfo&) = delete;
	RoundInfo& operator=(RoundInfo&&) = delete;

	bool _gameover;
	uint32_t _round;
	int16_t _year;
	Season _season;
	Daytime _daytime;
	Phase _phase;
};
