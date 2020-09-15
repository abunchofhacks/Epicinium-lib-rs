/**
 * Part of Epicinium
 * developed by A Bunch of Hacks.
 *
 * Copyright (c) 2017-2020 A Bunch of Hacks
 *
 * Epicinium is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Epicinium is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Affero General Public License for more details.
 *
 * You should have received a copy of the GNU Affero General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 *
 * [authors:]
 * Sander in 't Veld (sander@abunchofhacks.coop)
 * Daan Mulder (daan@abunchofhacks.coop)
 */
#include "language.hpp"
#include "source.hpp"

#if INTL_ENABLED
#include <locale.h>
#endif

#include "settings.hpp"


#if INTL_ENABLED
/* ######################################################################### */
Language::ScopedOverride::ScopedOverride(const std::string& override)
{
	LOGV << "Current LANGUAGE: " << getenv("LANGUAGE");
	std::stringstream strm;
	strm << override;
	if (getenv("LANGUAGE") != nullptr)
	{
		strm << ":" << getenv("LANGUAGE");
		_oldenv = getenv("LANGUAGE");
		_oldenvset = true;
	}
	std::string newenv = strm.str();
	if (setenv("LANGUAGE", newenv.c_str(), true) != 0)
	{
		LOGE << "Failed to set LANGUAGE to '" << newenv << "':"
			" " << errno << ": " << strerror(errno);
	}
	LOGV << "Current LANGUAGE: " << getenv("LANGUAGE");

	bind();
}

Language::ScopedOverride::~ScopedOverride()
{
	if (_oldenvset)
	{
		if (setenv("LANGUAGE", _oldenv.c_str(), true) != 0)
		{
			LOGE << "Failed to set LANGUAGE to '" << _oldenv << "':"
				" " << errno << ": " << strerror(errno);
		}
	}
	LOGV << "Current LANGUAGE: " << getenv("LANGUAGE");

	bind();
}

void Language::use(const Settings& settings)
{
	// Change LC_MESSAGES from "C" to the system default, e.g. "en_US",
	// because otherwise localization is disabled and LANGUAGE is ignored.
	LOGV << "Current locale: " << setlocale(LC_ALL, NULL);
	if (setlocale(LC_MESSAGES, "") == nullptr)
	{
		LOGE << "Failed to set locale to '':"
			" " << errno << ": " << strerror(errno);
	}
	LOGI << "Current locale: " << setlocale(LC_ALL, NULL);

	{
		LOGV << "Current LANGUAGE: " << getenv("LANGUAGE");
		std::stringstream strm;
		strm << settings.language.value("en_US");
		if (getenv("LANGUAGE") != nullptr)
		{
			strm << ":" << getenv("LANGUAGE");
		}
		std::string language = strm.str();
		if (setenv("LANGUAGE", language.c_str(), true) != 0)
		{
			LOGE << "Failed to set LANGUAGE to '" << language << "':"
				" " << errno << ": " << strerror(errno);
		}
	}
	LOGI << "Current LANGUAGE: " << getenv("LANGUAGE");

	bind();
}

void Language::bind()
{
	constexpr const char* TEXTDOMAIN = "epicinium";
	constexpr const char* LOCALEDIR = "bin/loc";
	constexpr const char* CODESET = "UTF-8";
	if (bindtextdomain(TEXTDOMAIN, LOCALEDIR) == nullptr)
	{
		LOGE << "Failed to bind textdomain:"
			" " << errno << ": " << strerror(errno);
	}
	if (bind_textdomain_codeset(TEXTDOMAIN, CODESET) == nullptr)
	{
		LOGE << "Failed to bind textdomain:"
			" " << errno << ": " << strerror(errno);
	}
	if (textdomain(TEXTDOMAIN) == nullptr)
	{
		LOGE << "Failed to bind textdomain:"
			" " << errno << ": " << strerror(errno);
	}
}

bool Language::isCurrentlyEnglish()
{
	if (getenv("LANGUAGE") != nullptr)
	{
		return (strncmp(getenv("LANGUAGE"), "en_", 3) == 0);
	}
	return false;
}

std::vector<std::string> Language::supportedTags()
{
	return {
		"en_US",
	};
}

std::vector<std::string> Language::experimentalTags()
{
	return {
		"nl_NL",
	};
}

std::string Language::getNameInOwnLanguage(const std::string& tag)
{
	Language::ScopedOverride override(tag);
	return getNameInActiveLanguage(tag);
}

std::string Language::getNameInActiveLanguage(const std::string& tag)
{
	if (tag == "en_US")
	{
		return _("English");
	}
	else if (tag == "nl_NL")
	{
		return _("Dutch");
	}
	else
	{
		LOGW << "Missing language name for '" << tag << "'";
		return "[" + tag + "]";
	}
}
/* ######################################################################### */
#else
/* ######################################################################### */
Language::ScopedOverride::ScopedOverride(const std::string&)
{
	LOGW << "Failed to switch languages because INTL_ENABLED is not true";
}

Language::ScopedOverride::~ScopedOverride()
{}

void Language::use(const Settings&)
{
	LOGW << "Cannot support other languages because INTL_ENABLED is not true";
}

void Language::bind()
{
	// Nothing to do.
}

bool Language::isCurrentlyEnglish()
{
	return true;
}

std::vector<std::string> Language::supportedTags()
{
	return {"en_US"};
}

std::vector<std::string> Language::experimentalTags()
{
	return {};
}

std::string Language::getNameInOwnLanguage(const std::string& tag)
{
	Language::ScopedOverride override(tag);
	return getNameInActiveLanguage(tag);
}

std::string Language::getNameInActiveLanguage(const std::string&)
{
	return "English";
}
/* ######################################################################### */
#endif
