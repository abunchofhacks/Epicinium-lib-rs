#pragma once
#include "header.hpp"

#include "version.hpp"

class Bible;


class Library
{
private:
	static Library* _installed;

public:
	Library();
	Library(const Library&) = delete;
	Library(Library&&) = delete;
	Library& operator=(const Library&) = delete;
	Library& operator=(Library&&) = delete;
	~Library();

private:
	std::vector<Version> _available;
	std::vector<std::unique_ptr<const Bible>> _cache;

	bool loadIndex(const std::string& filename);
	const Bible& loadBible(const Version& version);
	const Bible& loadBible(const std::string& rulesetname);

	static bool saveBible(const Version& version, const Bible& bible);
	static bool saveBible(const std::string& rulesetname, const Bible& bible);
	static bool addVersionToIndex(const Version& version);

public:
	void load(bool saveIfNew = false);
	void install();

	bool exists(const std::string& rulesetname);
	Bible get(const std::string& rulesetname);
	bool store(const std::string& rulesetname, const Json::Value& biblejson);

	std::string currentRuleset();
	std::string previousRuleset();
	std::string compatibleRuleset(const Version& version);
	std::string compatibleRuleset(const std::string& rulesetname);

	static std::string nameCurrentBible();
	static std::string nameCompatibleBible(const Version& version);
	static std::string nameCompatibleBible(const std::string& rulesetname);
	static bool existsBible(const std::string& rulesetname);
	static Bible getBible(const std::string& rulesetname);
	static bool storeBible(const std::string& rulesetname,
		const Json::Value& biblejson);
};
