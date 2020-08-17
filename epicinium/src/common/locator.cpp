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
