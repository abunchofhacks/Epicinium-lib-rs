#pragma once
#include "header.hpp"


/* Factories cause pollution in the global namespace. */
#pragma push_macro("major")
#undef major
#pragma push_macro("minor")
#undef minor
/* Factories cause pollution in the global namespace. */

struct Version
{
public:
	uint8_t major;
	uint8_t minor;
	uint8_t patch;
	uint8_t rcand;

	constexpr Version(int major, int minor, int patch, int rcand) :
		major(major),
		minor(minor),
		patch(patch),
		rcand(rcand)
	{}

	constexpr Version() :
		Version(undefined())
	{}

	static Version current();

	static Version latest();

	static constexpr Version prehistoric()
	{
		return Version(0, 0, 0, 0);
	}

	static constexpr Version undefined()
	{
		return Version(255, 255, 255, 255);
	}

	explicit Version(const std::string& str);
	explicit Version(const Json::Value& json);

	std::string toString() const;

	std::string name() const;

	constexpr bool isWellDefined() const
	{
		return ((major >   0 || minor >   0 || patch >   0)
			&&  (major < 255 || minor < 255 || patch < 255));
	}

	constexpr bool isDevelopment() const
	{
		return (major == 255 && minor == 255 && patch == 255 && rcand != 255);
	}

	constexpr bool isRelease() const
	{
		 return isWellDefined() && (rcand == 0);
	}

	constexpr bool isReleaseCandidate() const
	{
		return isWellDefined() && (rcand != 0);
	}

	bool isReleaseCandidateOf(const Version& other) const;

	constexpr Version release() const
	{
		return Version(major, minor, patch, 0);
	}

	bool tryBecomeParsed(const std::string& str);
};

std::ostream& operator<<(std::ostream& os, const Version& version);

bool operator==(const Version& a, const Version& b);
bool operator!=(const Version& a, const Version& b);

bool operator<(const Version& a, const Version& b);
bool operator<=(const Version& a, const Version& b);
bool operator>(const Version& a, const Version& b);
bool operator>=(const Version& a, const Version& b);

/* Factories cause pollution in the global namespace. */
#pragma pop_macro("minor")
#pragma pop_macro("major")
/* Factories cause pollution in the global namespace. */
