#include "map.hpp"
#include "source.hpp"

#include "system.hpp"


const char* stringify(const PoolType& type)
{
	switch (type)
	{
		case PoolType::NONE: return "none";
		case PoolType::MULTIPLAYER: return "multiplayer";
		case PoolType::CUSTOM: return "custom";
		case PoolType::DIORAMA: return "diorama";
	}
	return "";
}

PoolType parsePoolType(const std::string& str)
{
	for (size_t i = 0; i < POOLTYPE_SIZE; i++)
	{
		PoolType type = (PoolType) i;
		if (str.compare(stringify(type)) == 0) return type;
	}

	LOGE << "Cannot parse unknown PoolType '" << str << "'";
	DEBUG_ASSERT(false);
	return PoolType::NONE;
}

std::ostream& operator<<(std::ostream& os, const PoolType& type)
{
	return os << ::stringify(type);
}

std::string Map::filename(const std::string& name)
{
	return "maps/" + name + ".map";
}

std::string Map::oldfilename(const std::string& name)
{
	return "maps/" + name + ".json";
}

Json::Value Map::loadMetadata(const std::string& name)
{
	std::ifstream file;
	try
	{
		file.open(filename(name));
		if (file.is_open())
		{
			Json::Reader reader;
			Json::Value json;
			std::string line;

			if (!std::getline(file, line) || !reader.parse(line, json)
				|| !json.isObject())
			{
				return Json::nullValue;
			}

			return json;
		}
	}
	catch (const std::ifstream::failure& ignored)
	{
		return Json::nullValue;
	}
	return Json::nullValue;
}

bool Map::exists(const std::string& name)
{
	// Any file that exists exists.
	return System::isFile(filename(name));
}

const std::vector<std::string>& Map::pool()
{
	static std::vector<std::string> pool = {
		{"toad1v1"},
		{"spruce1v1"},
		{"small1v1"},
		{"oceanside1v1"},
		{"oasis1v1"},
		{"small3ffa"},
		{"oasis3ffa"},
		{"small4ffa"},
		{"beetle4ffa"},
		{"small8ffa"},
		{"cornered8ffa"},
	};
	return pool;
}

const std::vector<std::string>& Map::customPool()
{
	static std::vector<std::string> pool = {
		{"snowcut1v1"},
		{"challenge_morale"},
	};
	return pool;
}

const std::vector<std::string>& Map::userPool()
{
	static std::vector<std::string> pool = {
		{"Overlord_Vadim/Abandoned Places"},
		{"Overlord_Vadim/Civil War"},
		{"Overlord_Vadim/Great Duel"},
		{"Overlord_Vadim/Island of Augarn"},
		{"Overlord_Vadim/Mountain Crossings"},
		{"Overlord_Vadim/Neutrality Impossible"},
		{"Overlord_Vadim/Northmar's Heart"},
		{"Overlord_Vadim/Sins of the Past"},
		{"Overlord_Vadim/Town's Greatness"},
		{"Overlord_Vadim/Triumvirate Islands"},
		{"Overlord_Vadim/War Never Changes"},
		{"Overlord_Vadim/Winter Confrontation"},
	};
	return pool;
}

const std::vector<std::string>& Map::hiddenTutorialPool()
{
	static std::vector<std::string> pool = {
		{"tutorial"},
	};
	return pool;
}

const std::vector<std::string>& Map::hiddenChallengePool()
{
	static std::vector<std::string> pool = {
		{"challenge_showcase"},
		{"challenge_elimination"},
		{"challenge_trample"},
		{"challenge_investment"},
		{"challenge_morale"},
	};
	return pool;
}

std::string Map::DIORAMA_MAPNAME = "overview";

const std::vector<std::string>& Map::hiddenDioramaPool()
{
	static std::vector<std::string> pool = {
		DIORAMA_MAPNAME,
	};
	return pool;
}
