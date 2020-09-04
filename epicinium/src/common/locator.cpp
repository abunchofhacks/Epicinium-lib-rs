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
#include "locator.hpp"
#include "source.hpp"

#include "system.hpp"


std::string Locator::picture(const std::string& picturename)
{
	std::string filename = pictureFilename(picturename);
	if (System::isFile(filename)) return filename;
	else return "pictures/unknown.png";
}

std::string Locator::pictureFilename(const std::string& picturename)
{
	return "pictures/" + picturename + ".png";
}

std::string Locator::pictureName(const std::string& filename)
{
	size_t slashpos = filename.find_first_of('/');
	size_t dotpos = filename.find_last_of('.');
	if (filename.substr(0, slashpos) == "pictures"
		&& filename.substr(dotpos, std::string::npos) == ".png")
	{
		return filename.substr(slashpos + 1, dotpos - (slashpos + 1));
	}
	return "";
}

std::string Locator::rulesetFilename(const std::string& rulesetname)
{
	return "rulesets/" + rulesetname + ".json";
}

std::string Locator::rulesetName(const std::string& filename)
{
	size_t slashpos = filename.find_first_of('/');
	size_t dotpos = filename.find_last_of('.');
	if (filename.substr(0, slashpos) == "rulesets"
		&& filename.substr(dotpos, std::string::npos) == ".json")
	{
		return filename.substr(slashpos + 1, dotpos - (slashpos + 1));
	}
	return "";
}

std::string Locator::fzmodelFilename(const std::string& fzmodelname)
{
	return "sessions/" + fzmodelname + ".fzm";
}

std::string Locator::fzmodelName(const std::string& filename)
{
	size_t slashpos = filename.find_first_of('/');
	size_t dotpos = filename.find_last_of('.');
	if (filename.substr(0, slashpos) == "sessions"
		&& filename.substr(dotpos, std::string::npos) == ".fzm")
	{
		return filename.substr(slashpos + 1, dotpos - (slashpos + 1));
	}
	return "";
}
