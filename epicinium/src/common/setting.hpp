#pragma once
#include "header.hpp"


enum class ScreenMode : uint8_t { WINDOWED, BORDERLESS, FULLSCREEN, DESKTOP };
enum class SelectorMode : uint8_t { CONTEXT, FIGURE };
enum class PatchMode : uint8_t { NONE, SERVER, ITCHIO, GAMEJOLT };

class Settings;

template <typename T>
class Setting
{
private:
	template <typename S>
	friend class Setting;

	friend Settings;

	Settings* const _owner;
	const size_t _index;
	const char* const _name; // nullable
	const char* const _altname; // nullable

	bool _defined;
	T _value;

public:
	Setting(Settings* owner, /*nullable*/ const char* name);
	Setting(Settings* owner, const char* name, const char* altname);

	Setting& operator=(const T& value);
	void override(const T& value);
	void reset();
	bool defined() const;
	const Setting& definition() const;
	const T& value() const;
	const T& value(const T& fallback) const;

private:
	bool parse(const Json::Value& root);
	bool parse(const Json::Value& root, const char* name);
	void store(Json::Value& root) const;
};
