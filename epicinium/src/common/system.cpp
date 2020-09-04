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
#include "system.hpp"
#include "source.hpp"


#ifdef PLATFORMUNIX
/* ######################################### UNIX ######################################### */

#include <unistd.h>
#include <sys/stat.h>
#include <time.h>


void System::touchDirectory(const std::string& dirname)
{
	if (dirname.empty() || dirname == "/") return;

	touchParentDirectory(dirname);

	struct stat buffer;
	if (::stat(dirname.c_str(), &buffer) == 0 && S_ISDIR(buffer.st_mode)) return;

	::mkdir(dirname.c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
}

void System::touchFile(const std::string& filename)
{
	if (filename.empty() || filename == "/") return;

	touchParentDirectory(filename);

	struct stat buffer;
	if (::stat(filename.c_str(), &buffer) == 0 && S_ISREG(buffer.st_mode)) return;

	std::ofstream file(filename, std::ios::binary | std::ios::app);
}

void System::touchParentDirectory(const std::string& filename)
{
	size_t parent = filename.find_last_of("/");
	if (parent != std::string::npos)
	{
		touchDirectory(filename.substr(0, parent));
	}
}

bool System::isDirectory(const std::string& filename)
{
	if (filename.empty()) return false;

	struct stat buffer;
	if (::stat(filename.c_str(), &buffer) != 0 || !S_ISDIR(buffer.st_mode)) return false;

	return true;
}

bool System::isFile(const std::string& filename)
{
	if (filename.empty() || filename == "/") return false;

	struct stat buffer;
	if (::stat(filename.c_str(), &buffer) != 0 || !S_ISREG(buffer.st_mode)) return false;

	return true;
}

bool System::isFileNonempty(const std::string& filename)
{
	struct stat buffer;
	if (::stat(filename.c_str(), &buffer) != 0 || !S_ISREG(buffer.st_mode)) return false;

	std::ifstream file(filename, std::ios::binary);

	return (file.peek() != std::ifstream::traits_type::eof());
}

bool System::isFileExecutable(const std::string& filename)
{
	struct stat buffer;
	if (::stat(filename.c_str(), &buffer) != 0 || !S_ISREG(buffer.st_mode)) return false;

	return (buffer.st_mode & S_IXUSR);
}

void System::makeFileExecutable(const std::string& filename)
{
	struct stat buffer;
	if (::stat(filename.c_str(), &buffer) != 0 || !S_ISREG(buffer.st_mode)) return;

	::chmod(filename.c_str(), buffer.st_mode | S_IRWXU | S_IRWXG);
}

std::string System::getHttpModificationTimeString(const std::string& filename)
{
	struct stat buffer;
	if (::stat(filename.c_str(), &buffer) != 0 || !S_ISREG(buffer.st_mode)) return "";

	struct tm* mtime = gmtime(&(buffer.st_mtime));
	char stringbuffer[100];
	strftime(stringbuffer, 100, "%a, %d %b %Y %H:%M:%S GMT", mtime);
	return stringbuffer;
}

void System::purgeFile(const std::string& filename)
{
	if (!isFile(filename)) return;

	std::ofstream file(filename, std::ios::binary | std::ios::trunc);
}

void System::unlinkFile(const std::string& filename)
{
	if (!isFile(filename)) return;

	unlink(filename.c_str());
}

void System::moveFile(const std::string& filename, const std::string& dest)
{
	if (!isFile(filename)) return;

	touchFile(dest);
	if (!isFile(dest)) return;

	unlink(dest.c_str());
	if (isFile(dest)) return;

	rename(filename.c_str(), dest.c_str());
}

void System::copyFile(const std::string& filename, const std::string& dest)
{
	if (!isFile(filename)) return;

	touchFile(dest);
	if (!isFile(dest)) return;

	std::ifstream source(filename, std::ios::binary);
	std::ofstream target(dest, std::ios::binary | std::ios::trunc);

	target << source.rdbuf();
}

bool System::isLink(const std::string& filename)
{
	struct stat buffer;
	if (::lstat(filename.c_str(), &buffer) != 0) return false;

	return S_ISLNK(buffer.st_mode);
}

std::string System::readLink(const std::string& filename)
{
	struct stat buffer;
	if (::lstat(filename.c_str(), &buffer) != 0) return "";
	if (!S_ISLNK(buffer.st_mode)) return "";

	size_t size = buffer.st_size;
	std::vector<char> pathbuffer(size);
	int used = ::readlink(filename.c_str(), pathbuffer.data(), size);
	if (used < 0)
	{
		return "";
	}

	return std::string(pathbuffer.begin(), pathbuffer.begin() + used);
}

void System::makeLink(const std::string& filename, const char* target)
{
	if (isFile(filename)) return;

	if (::symlink(target, filename.c_str()) != 0)
	{
		return;
	}
}

/* ######################################### UNIX ######################################### */
#else
/* ######################################## WINDOWS ####################################### */

#include <sys/stat.h>
#include <time.h>
#include <windows.h>

#include "clock.hpp"
#include "keycode.hpp"


void System::touchDirectory(const std::string& dirname)
{
	if (dirname.empty() || dirname == "/") return;

	touchParentDirectory(dirname);

	struct stat buffer;
	if (::stat(dirname.c_str(), &buffer) == 0 && S_ISDIR(buffer.st_mode)) return;

	::mkdir(dirname.c_str());
}

void System::touchFile(const std::string& filename)
{
	if (filename.empty() || filename == "/") return;

	touchParentDirectory(filename);

	struct stat buffer;
	if (::stat(filename.c_str(), &buffer) == 0 && S_ISREG(buffer.st_mode)) return;

	std::ofstream file(filename, std::ios::binary | std::ios::app);
}

void System::touchParentDirectory(const std::string& filename)
{
	size_t parent = filename.find_last_of("/");
	if (parent != std::string::npos)
	{
		touchDirectory(filename.substr(0, parent));
	}
}

bool System::isDirectory(const std::string& filename)
{
	if (filename.empty()) return false;

	struct stat buffer;
	if (::stat(filename.c_str(), &buffer) != 0 || !S_ISDIR(buffer.st_mode)) return false;

	return true;
}

bool System::isFile(const std::string& filename)
{
	if (filename.empty() || filename == "/") return false;

	struct stat buffer;
	if (::stat(filename.c_str(), &buffer) != 0 || !S_ISREG(buffer.st_mode)) return false;

	return true;
}

bool System::isFileNonempty(const std::string& filename)
{
	if (!isFile(filename)) return false;

	std::ifstream file(filename, std::ios::binary);

	return (file.peek() != std::ifstream::traits_type::eof());
}

bool System::isFileExecutable(const std::string& filename)
{
	if (!isFile(filename)) return false;

	// All files are executable in Windows, but for sanity's sake we look at the extension.
	size_t dot = filename.find_last_of(".");
	if (dot == std::string::npos) return false;
	std::string extension = filename.substr(dot + 1);
	return (extension == "exe" || extension == "dll");
}

void System::makeFileExecutable(const std::string&)
{
	// All files are executable in Windows.
}

std::string System::getHttpModificationTimeString(const std::string& filename)
{
	struct stat buffer;
	if (::stat(filename.c_str(), &buffer) != 0 || !S_ISREG(buffer.st_mode)) return "";

	struct tm* mtime = gmtime(&(buffer.st_mtime));
	char stringbuffer[100];
	strftime(stringbuffer, 100, "%a, %d %b %Y %H:%M:%S GMT", mtime);
	return stringbuffer;
}

void System::purgeFile(const std::string& filename)
{
	if (!isFile(filename)) return;

	std::ofstream file(filename, std::ios::binary | std::ios::trunc);
}

void System::unlinkFile(const std::string& filename)
{
	if (!isFile(filename)) return;

	auto timestampMs = EpochClock::milliseconds();
	uint16_t key = rand() % (1 << 16);
	std::string hash = ::keycode(key, timestampMs);

	std::string dest = "downloads\\" + filename + "." + hash + ".old";

	touchFile(dest);
	if (!isFile(dest)) return;

	DeleteFileA(dest.c_str());
	if (isFile(dest)) return;

	MoveFileA(filename.c_str(), dest.c_str());

	DWORD attributes = GetFileAttributesA(dest.c_str());
	SetFileAttributesA(dest.c_str(), attributes | FILE_ATTRIBUTE_HIDDEN);

	std::ofstream oldlist("downloads\\old.list", std::ofstream::app);
	oldlist << dest << std::endl;
}

void System::moveFile(const std::string& filename, const std::string& dest)
{
	if (!isFile(filename)) return;

	touchFile(dest);
	if (!isFile(dest)) return;

	DeleteFileA(dest.c_str());
	if (isFile(dest)) return;

	MoveFileA(filename.c_str(), dest.c_str());
}

void System::copyFile(const std::string& filename, const std::string& dest)
{
	if (!isFile(filename)) return;

	touchFile(dest);
	if (!isFile(dest)) return;

	std::ifstream source(filename, std::ios::binary);
	std::ofstream target(dest, std::ios::binary | std::ios::trunc);

	target << source.rdbuf();
}

bool System::isLink(const std::string&)
{
	LOGE << "Unimplemented";
	DEBUG_ASSERT(false);
	return false;
}

std::string System::readLink(const std::string&)
{
	LOGE << "Unimplemented";
	DEBUG_ASSERT(false);
	return "";
}

void System::makeLink(const std::string&, const char*)
{
	LOGE << "Unimplemented";
	DEBUG_ASSERT(false);
}

/* ######################################## WINDOWS ####################################### */
#endif



static 	bool doSimpleStorageTest()
{
	std::string filename = "logs/storage.log";
	std::string teststring = "This file was automatically generated.";
	{
		System::touchFile(filename);
		std::ofstream file;
		file.open(filename, std::ofstream::out | std::ofstream::trunc);
		file << teststring << std::endl;
	}
	{
		std::ifstream file;
		std::string line;
		file.open(filename);
		if (!file.is_open() || !std::getline(file, line)
			|| line != teststring)
		{
			return true;
		}
	}
	return false;
}

bool System::hasStorageIssues()
{
	// Do the simple storage test the first time this function is called.
	static const bool has = doSimpleStorageTest();
	return has;
}
