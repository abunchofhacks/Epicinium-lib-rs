#pragma once
#include "header.hpp"

#include "logcallback.h"

class Settings;


class LogInstaller
{
public:
	explicit LogInstaller(const Settings& settings);
	explicit LogInstaller(const std::string& name, int rollback,
		const std::string& level = "", const std::string& perf = "");
	explicit LogInstaller(log_callback_fn callback, uint8_t severity);

private:
	const std::string _name;
	const std::string _level;
	const std::string _perf;
	const int _rollback;

	int _verboserollback = 0;

public:
	void install();

	LogInstaller& withSeparateVerboseRollback(int verboserollback)
	{
		_verboserollback = verboserollback;
		return *this;
	}

	std::string perflogfilename() const;

private:
	static std::string _logsfolder;

public:
	static void setRoot(const std::string& root);
};
