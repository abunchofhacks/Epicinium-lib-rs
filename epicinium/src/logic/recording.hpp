#pragma once
#include "header.hpp"

enum class Player : uint8_t;


class Recording
{
public:
	explicit Recording();
	explicit Recording(const std::string& name);
	~Recording();
	Recording(const Recording&) = delete;
	Recording(Recording&& that);
	Recording& operator=(const Recording&) = delete;
	Recording& operator=(Recording&& that);

private:
	std::string _name;
	std::string _filename;
	std::unique_ptr<Json::Value> _metadata;
	bool _listed = true;

public:
	const std::string& name()     const { return _name;     }
	const std::string& filename() const { return _filename; }

	static std::string filename(const std::string& name);

	explicit operator bool() const { return !_name.empty(); }

	bool operator==(const Recording& other) { return _name == other._name; }

	void start();
	void start(const std::string& name);
	void end();

	void addMetadata(Json::Value& metadata);

	Json::Value metadata();

	std::vector<Player> getPlayers();
	std::string getRuleset();

	static bool exists(const std::string& name);

	static std::vector<Recording> list(int count);

private:
	static std::string _recordingsfolder;
	static std::string _historyfilename;

public:
	static void setRoot(const std::string& root);
};
