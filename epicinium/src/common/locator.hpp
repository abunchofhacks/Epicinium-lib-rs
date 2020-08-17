#pragma once
#include "header.hpp"


class Locator
{
public:
	static std::string picture(const std::string& picturename);
	static std::string pictureFilename(const std::string& picturename);
	static std::string pictureName(const std::string& filename);
	static std::string rulesetFilename(const std::string& rulesetname);
	static std::string rulesetName(const std::string& filename);
	static std::string fzmodelFilename(const std::string& fzmodelname);
	static std::string fzmodelName(const std::string& filename);
};
