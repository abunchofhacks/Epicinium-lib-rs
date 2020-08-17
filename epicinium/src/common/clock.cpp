#include "clock.hpp"
#include "source.hpp"

#include <chrono>


uint64_t EpochClock::seconds()
{
	// For some uses we care about time relative to earlier runs of the program,
	// so we cannot use steady_clock and use system_clock instead.
	auto currentTimestampMs =
		std::chrono::duration_cast<std::chrono::seconds>(
			std::chrono::system_clock::now().time_since_epoch());
	return currentTimestampMs.count();
}

uint64_t EpochClock::milliseconds()
{
	// For some uses we care about time relative to earlier runs of the program,
	// so we cannot use steady_clock and use system_clock instead.
	auto currentTimestampMs =
		std::chrono::duration_cast<std::chrono::milliseconds>(
			std::chrono::system_clock::now().time_since_epoch());
	return currentTimestampMs.count();
}

uint64_t SteadyClock::milliseconds()
{
	// We use steady_clock instead of system_clock, because we only care about
	// time relative to the start of the program, not about timezones or dates.
	auto currentTimestampMs =
		std::chrono::duration_cast<std::chrono::milliseconds>(
			std::chrono::steady_clock::now().time_since_epoch());
	return currentTimestampMs.count();
}
