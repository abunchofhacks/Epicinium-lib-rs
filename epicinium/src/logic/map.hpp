#pragma once
#include "header.hpp"


enum class PoolType : uint8_t
{
	NONE = 0,
	MULTIPLAYER,
	CUSTOM,
	DIORAMA,
};

constexpr size_t POOLTYPE_SIZE = ((size_t) PoolType::DIORAMA) + 1;

const char* stringify(const PoolType& type);
PoolType parsePoolType(const std::string& str);
std::ostream& operator<<(std::ostream& os, const PoolType& type);

class Map
{
public:
	static std::string filename(const std::string& name);
	static std::string oldfilename(const std::string& name);

	static Json::Value loadMetadata(const std::string& name);

	static bool exists(const std::string& name);

	static const std::vector<std::string>& pool();
	static const std::vector<std::string>& customPool();
	static const std::vector<std::string>& userPool();
	static const std::vector<std::string>& hiddenTutorialPool();
	static const std::vector<std::string>& hiddenChallengePool();
	static const std::vector<std::string>& hiddenDioramaPool();

	static std::string DIORAMA_MAPNAME;
};
