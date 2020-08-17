#pragma once
#include "header.hpp"

#include "setting.hpp"



class Settings
{
private:
	// Pre-initialized.
	Settings(std::unique_ptr<Settings> fallback);

	// Default initialized.
	Settings();

	// The layer below the top level Settings.
	Settings(const std::string& fname, std::unique_ptr<Settings> fallback);

public:
	// Standard application settings.
	Settings(const std::string& fname, int argc, const char* const argv[]);

	// Unsaveable library settings.
	Settings(int argc, const char* const argv[]);

	// Unsaveable copied settings.
	explicit Settings(Json::Value& json);

	Settings(const Settings&) = delete;
	Settings(Settings&&) = delete;
	Settings& operator=(const Settings&) = delete;
	Settings& operator=(Settings&&) = delete;
	~Settings() = default;

private:
	std::unique_ptr<Settings> _fallback;

	std::vector<Setting<bool>*> _boollist;
	std::vector<Setting<ScreenMode>*> _screenmodelist;
	std::vector<Setting<SelectorMode>*> _selectormodelist;
	std::vector<Setting<PatchMode>*> _patchmodelist;
	std::vector<Setting<int>*> _intlist;
	std::vector<Setting<float>*> _floatlist;
	std::vector<Setting<std::string>*> _stringlist;

	friend Setting<bool>;
	friend Setting<ScreenMode>;
	friend Setting<SelectorMode>;
	friend Setting<PatchMode>;
	friend Setting<int>;
	friend Setting<float>;
	friend Setting<std::string>;

	size_t push(Setting<bool>*);
	size_t push(Setting<ScreenMode>*);
	size_t push(Setting<SelectorMode>*);
	size_t push(Setting<PatchMode>*);
	size_t push(Setting<int>*);
	size_t push(Setting<float>*);
	size_t push(Setting<std::string>*);

	Setting<bool>& get(size_t index, bool dummy);
	Setting<ScreenMode>& get(size_t index, ScreenMode dummy);
	Setting<SelectorMode>& get(size_t index, SelectorMode dummy);
	Setting<PatchMode>& get(size_t index, PatchMode dummy);
	Setting<int>& get(size_t index, int dummy);
	Setting<float>& get(size_t index, float dummy);
	Setting<std::string>& get(size_t index, const std::string& dummy);

	std::string _filename;

	bool _askedForHelp;
	std::vector<std::string> _unknowns;

	bool saveable();

public:
	Setting<std::string> logname;
	Setting<std::string> loglevel;
	Setting<int> logrollback;
	Setting<std::string> perflog;
	Setting<std::string> dataFolder;
	Setting<int> seed;
	Setting<int> display;
	Setting<ScreenMode> screenmode;
	Setting<int> windowX;
	Setting<int> windowY;
	Setting<int> width;
	Setting<int> height;
	Setting<int> scale;
	Setting<int> framerate;
	Setting<bool> finishRendering;
	Setting<bool> discord;
	Setting<bool> allowDiscordLogin;
	Setting<bool> useApi;
	Setting<std::string> server;
	Setting<int> port;
	Setting<PatchMode> patchmode;
	Setting<SelectorMode> selectormode;
	Setting<std::string> stomtToken;
	Setting<std::string> memento;
	Setting<bool> cameraScrollingWasd;
	Setting<bool> cameraScrollingArrows;
	Setting<bool> cameraScrollingEdge;
	Setting<bool> allowScrollingWhileActing;
	Setting<bool> allowScrollingWhilePanning;
	Setting<bool> allowRedundantStop;
	Setting<bool> allowRedundantCultivate;
	Setting<bool> allowRedundantUpgrade;
	Setting<bool> allowPowerless;
	Setting<std::string> slackname;
	Setting<std::string> slackurl;
	Setting<std::string> discordurl;
	Setting<int> audioBufferSize;
	Setting<float> masterVolume;
	Setting<float> gameplayVolume;
	Setting<float> musicVolume;
	Setting<bool> skipAnimations;
	Setting<bool> skipLighting;
	Setting<bool> skipPanning;
	Setting<bool> silentPlanningBell;
	Setting<bool> hideIdleAnimations;
	Setting<bool> hideLayouts;
	Setting<bool> showViewport;

private:
	Setting<std::string> settings;

	static PatchMode detectPatchMode();

	void setFallback(const std::string& filename);

	bool parse(const Json::Value& json);

	void store(Json::Value& json);

public:
	bool override(const char* arg);

	Settings& defaults();

	void load();
	void save();

	Json::Value flattenIntoJson();

	bool askedForHelp() const { return _askedForHelp; }
	void help() const;
};