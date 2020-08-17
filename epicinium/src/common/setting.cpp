#include "setting.hpp"
#include "source.hpp"

#include "settings.hpp"


static const char* stringify(const ScreenMode& mode)
{
	switch (mode)
	{
		case ScreenMode::WINDOWED:    return "windowed";
		case ScreenMode::BORDERLESS:  return "windowed-borderless";
		case ScreenMode::FULLSCREEN:  return "fullscreen";
		case ScreenMode::DESKTOP:     return "fullscreen-desktop";
	}
	return "";
}

static const char* stringify(const SelectorMode& mode)
{
	switch (mode)
	{
		case SelectorMode::CONTEXT:   return "context";
		case SelectorMode::FIGURE:    return "figure";
	}
	return "";
}

static const char* stringify(const PatchMode& mode)
{
	switch (mode)
	{
		case PatchMode::NONE:         return "none";
		case PatchMode::SERVER:       return "server";
		case PatchMode::ITCHIO:       return "itchio";
		case PatchMode::GAMEJOLT:     return "gamejolt";
	}
	return "";
}

template <typename T>
Setting<T>::Setting(Settings* owner, const char* name) :
	Setting<T>(owner, name, nullptr)
{}

template <typename T>
Setting<T>::Setting(Settings* owner, const char* name, const char* alt) :
	_owner(owner),
	_index(_owner->push(this)),
	_name(name),
	_altname(alt),
	_defined(false)
{}

template <typename T>
Setting<T>& Setting<T>::operator=(const T& value)
{
	if (!_owner->saveable() && _owner->_fallback)
	{
		return _owner->_fallback->get(_index, /*type=*/value).operator=(value);
	}

	_defined = true;
	_value = value;
	return *this;
}

template <typename T>
void Setting<T>::override(const T& value)
{
	_defined = true;
	_value = value;
}

template <typename T>
void Setting<T>::reset()
{
	_defined = false;
}

template <typename T>
bool Setting<T>::defined() const
{
	if (_defined) return true;

	if (_owner->_fallback)
	{
		return _owner->_fallback->get(_index, /*type=*/_value).defined();
	}

	return false;
}

template <typename T>
const Setting<T>& Setting<T>::definition() const
{
	if (_defined) return *this;

	if (_owner->_fallback)
	{
		return _owner->_fallback->get(_index, /*type=*/_value).definition();
	}

	// LogInstaller might not have been called at this point.
	DEBUG_ASSERT(false && "Settings<T>::definition() undefined when called.");
	return *this;
}

template <typename T>
const T& Setting<T>::value() const
{
	if (_defined) return _value;

	if (_owner->_fallback)
	{
		return _owner->_fallback->get(_index, /*type=*/_value).value();
	}

	// LogInstaller might not have been called at this point.
	DEBUG_ASSERT(false && "Settings<T>::value() undefined when called.");
	return _value;
}

template <typename T>
const T& Setting<T>::value(const T& fallback) const
{
	if (_defined) return _value;

	if (_owner->_fallback)
	{
		return _owner->_fallback->get(_index, /*type=*/_value).value(fallback);
	}

	return fallback;
}

template <typename T>
bool Setting<T>::parse(const Json::Value& root)
{
	if (_name != nullptr && root.isMember(_name))
	{
		return parse(root, _name);
	}
	else if (_altname != nullptr && root.isMember(_altname))
	{
		return parse(root, _altname);
	}
	else return false;
}

template <>
bool Setting<bool>::parse(const Json::Value& root, const char* name)
{
	auto& x = root[name];
	if (x.isBool())
	{
		_defined = true;
		_value = x.asBool();
		return true;
	}
	else if (x.isInt())
	{
		_defined = true;
		_value = (x.asInt());
		return true;
	}
	else if (x.isString())
	{
		_defined = true;
		if (x.asString() == "true") _value = 1;
		else if (x.asString() == "false") _value = 0;
		else _value = std::stoi(x.asString());
		return true;
	}
	else if (!x.isNull())
	{
		std::cerr << "Invalid value for '" << name << "'" << std::endl;
		return false;
	}
	else return false;
}

template <>
bool Setting<int>::parse(const Json::Value& root, const char* name)
{
	auto& x = root[name];
	if (x.isInt())
	{
		_defined = true;
		_value = x.asInt();
		return true;
	}
	else if (x.isBool())
	{
		_defined = true;
		_value = x.asBool() ? 1 : 0;
		return true;
	}
	else if (x.isString())
	{
		_defined = true;
		if (x.asString() == "true") _value = 1;
		else if (x.asString() == "false") _value = 0;
		else _value = std::stoi(x.asString());
		return true;
	}
	else if (!x.isNull())
	{
		std::cerr << "Invalid value for '" << name << "'" << std::endl;
		return false;
	}
	else return false;
}

template <>
bool Setting<float>::parse(const Json::Value& root, const char* name)
{
	auto& x = root[name];
	if (x.isDouble())
	{
		_defined = true;
		_value = x.asFloat();
		return true;
	}
	else if (x.isInt())
	{
		_defined = true;
		_value = x.asInt();
		return true;
	}
	else if (x.isBool())
	{
		_defined = true;
		_value = x.asBool() ? 1.0f : 0.0f;
		return true;
	}
	else if (x.isString())
	{
		_defined = true;
		if (x.asString() == "true") _value = 1;
		else if (x.asString() == "false") _value = 0;
		else _value = std::stof(x.asString());
		return true;
	}
	else if (!x.isNull())
	{
		std::cerr << "Invalid value for '" << name << "'" << std::endl;
		return false;
	}
	else return false;
}

template <>
bool Setting<std::string>::parse(const Json::Value& root, const char* name)
{
	auto& x = root[name];
	if (x.isString())
	{
		_defined = true;
		_value = x.asString();
		return true;
	}
	else if (!x.isNull())
	{
		std::cerr << "Invalid value for '" << name << "'" << std::endl;
		return false;
	}
	else return false;
}

template <>
bool Setting<ScreenMode>::parse(const Json::Value& root, const char* name)
{
	auto& x = root[name];
	if (x.isString())
	{
		_defined = true;
		std::string str = x.asString();
		if      (str == "windowed")            _value = ScreenMode::WINDOWED;
		else if (str == "windowed-borderless") _value = ScreenMode::BORDERLESS;
		else if (str == "borderless")          _value = ScreenMode::BORDERLESS;
		else if (str == "fullscreen")          _value = ScreenMode::FULLSCREEN;
		else if (str == "fullscreen-desktop")  _value = ScreenMode::DESKTOP;
		else if (str == "desktop")             _value = ScreenMode::DESKTOP;
		else
		{
			_defined = false;
			std::cerr << "Unknown screenmode '" << str << "'" << std::endl;
			return false;
		}
		return true;
	}
	else if (!x.isNull())
	{
		std::cerr << "Invalid value for '" << name << "'" << std::endl;
		return false;
	}
	else return false;
}

template <>
void Setting<ScreenMode>::store(Json::Value& root) const
{
	if (_name == nullptr) return;

	if (_defined)
	{
		root[_name] = stringify(_value);
	}
	else
	{
		root.removeMember(_name);
	}
}

template <>
bool Setting<SelectorMode>::parse(const Json::Value& root, const char* name)
{
	auto& x = root[name];
	if (x.isString())
	{
		_defined = true;
		std::string str = x.asString();
		if      (str == "context")             _value = SelectorMode::CONTEXT;
		else if (str == "figure")              _value = SelectorMode::FIGURE;
		else
		{
			_defined = false;
			std::cerr << "Unknown selectormode '" << str << "'" << std::endl;
			return false;
		}
		return true;
	}
	else if (!x.isNull())
	{
		std::cerr << "Invalid value for '" << name << "'" << std::endl;
		return false;
	}
	else return false;
}

template <>
void Setting<SelectorMode>::store(Json::Value& root) const
{
	if (_name == nullptr) return;

	if (_defined)
	{
		root[_name] = stringify(_value);
	}
	else
	{
		root.removeMember(_name);
	}
}

template <>
bool Setting<PatchMode>::parse(const Json::Value& root, const char* name)
{
	auto& x = root[name];
	if (x.isString())
	{
		_defined = true;
		std::string str = x.asString();
		if      (str == "none")                _value = PatchMode::NONE;
		else if (str == "server")              _value = PatchMode::SERVER;
		else if (str == "itchio")              _value = PatchMode::ITCHIO;
		else if (str == "gamejolt")            _value = PatchMode::GAMEJOLT;
		else
		{
			_defined = false;
			std::cerr << "Unknown patchmode '" << str << "'" << std::endl;
			return false;
		}
		return true;
	}
	else if (!x.isNull())
	{
		std::cerr << "Invalid value for '" << name << "'" << std::endl;
		return false;
	}
	else return false;
}

template <>
void Setting<PatchMode>::store(Json::Value& root) const
{
	if (_name == nullptr) return;

	if (_defined)
	{
		root[_name] = stringify(_value);
	}
	else
	{
		root.removeMember(_name);
	}
}

template <typename T>
void Setting<T>::store(Json::Value& root) const
{
	if (_name == nullptr) return;

	if (_defined)
	{
		root[_name] = _value;
	}
	else
	{
		root.removeMember(_name);
	}
}

template class Setting<bool>;
template class Setting<ScreenMode>;
template class Setting<SelectorMode>;
template class Setting<PatchMode>;
template class Setting<int>;
template class Setting<float>;
template class Setting<std::string>;