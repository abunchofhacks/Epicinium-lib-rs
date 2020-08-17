#pragma once
#include "header.hpp"


namespace System
{
	bool isDirectory(const std::string& filename);
	bool isFile(const std::string& filename);
	bool isFileNonempty(const std::string& filename);
	bool isFileExecutable(const std::string& filename);
	void makeFileExecutable(const std::string& filename);

	std::string getHttpModificationTimeString(const std::string& filename);

	void touchFile(const std::string& filename);
	void touchDirectory(const std::string& dirname);
	void touchParentDirectory(const std::string& filename);

	void purgeFile(const std::string& filename);
	void unlinkFile(const std::string& filename);

	void moveFile(const std::string& filename, const std::string& dest);
	void copyFile(const std::string& filename, const std::string& dest);

	bool isLink(const std::string& filename);
	std::string readLink(const std::string& filename);
	void makeLink(const std::string& filename, const char* target);

	bool hasStorageIssues();
}
