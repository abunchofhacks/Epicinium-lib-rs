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


#if defined __has_include
#   if __has_include(<filesystem>)
#     include <filesystem>
      namespace fs = std::filesystem;
#   else
#     include <experimental/filesystem>
      namespace fs = std::experimental::filesystem;
#   endif
#else
#   include <filesystem>
    namespace fs = std::filesystem;
#endif

std::vector<std::string> System::listDirectory(const std::string& dirname,
	const std::string& extension)
{
	std::string extensionPattern = extension;
	if (extensionPattern.empty())
	{
		extensionPattern = ".non-existing-LkYlNtDpRCybaYTWpdyMvHGnJtHsY";
	}
	else if (extensionPattern[0] != '.')
	{
		extensionPattern = "." + extensionPattern;
	}

	std::vector<std::string> filenames;
	if (!System::isDirectory(dirname))
	{
		return filenames;
	}
	for(const auto& p : fs::directory_iterator(dirname))
	{
		if (p.path().extension() == extensionPattern)
		{
			filenames.push_back(p.path().stem().string());
		}
	}
	return filenames;
}


#ifdef PLATFORMUNIX
/* ################################## UNIX ################################## */

#include <unistd.h>
#include <sys/stat.h>
#include <time.h>
#include <limits.h>


FILE* System::fopen(const std::string& filename, const char* mode)
{
	return ::fopen(filename.c_str(), mode);
}

std::ifstream System::ifstream(const std::string& filename)
{
	return std::ifstream(filename);
}

std::ifstream System::ifstream(const std::string& filename,
	std::ios_base::openmode mode)
{
	return std::ifstream(filename, mode);
}

std::ofstream System::ofstream(const std::string& filename)
{
	return std::ofstream(filename);
}

std::ofstream System::ofstream(const std::string& filename,
	std::ios_base::openmode mode)
{
	return std::ofstream(filename, mode);
}

void System::touchDirectory(const std::string& dirname)
{
	if (dirname.empty() || dirname == "/")
	{
		LOGE << "Cannot touch dirname '" << dirname << "'";
		return;
	}

	touchParentDirectory(dirname);

	struct stat buffer;
	if (::stat(dirname.c_str(), &buffer) == 0 && S_ISDIR(buffer.st_mode))
	{
		// Directory already exists, no need to touch it.
		return;
	}

	::mkdir(dirname.c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
}

void System::touchFile(const std::string& filename)
{
	if (filename.empty() || filename == "/")
	{
		LOGE << "Cannot touch filename '" << filename << "'";
		return;
	}

	touchParentDirectory(filename);

	struct stat buffer;
	if (::stat(filename.c_str(), &buffer) == 0 && S_ISREG(buffer.st_mode))
	{
		// File already exists, no need to touch it.
		return;
	}

	System::ofstream(filename, std::ios::binary | std::ios::app);
}

void System::touchParentDirectory(const std::string& filename)
{
	size_t parent = filename.find_last_of("/");
	if (parent != 0 && parent != std::string::npos)
	{
		touchDirectory(filename.substr(0, parent));
	}
}

bool System::isDirectory(const std::string& filename)
{
	if (filename.empty())
	{
		LOGE << "Cannot stat filename '" << filename << "'";
		return false;
	}

	struct stat buffer;
	if (::stat(filename.c_str(), &buffer) != 0)
	{
		// The file does not exist.
		return false;
	}

	return S_ISDIR(buffer.st_mode);
}

bool System::isFile(const std::string& filename)
{
	if (filename.empty() || filename == "/")
	{
		LOGE << "Cannot stat filename '" << filename << "'";
		return false;
	}

	struct stat buffer;
	if (::stat(filename.c_str(), &buffer) != 0)
	{
		// The file does not exist.
		return false;
	}

	return S_ISREG(buffer.st_mode);
}

bool System::isFileNonempty(const std::string& filename)
{
	if (!System::isFile(filename))
	{
		return false;
	}

	std::ifstream file = System::ifstream(filename, std::ios::binary);

	return (file.peek() != std::ifstream::traits_type::eof());
}

bool System::isFileExecutable(const std::string& filename)
{
	if (!System::isFile(filename))
	{
		return false;
	}

	struct stat buffer;
	if (::stat(filename.c_str(), &buffer) != 0)
	{
		LOGE << "Failed to stat '" << filename << "'";
		return false;
	}

	return (buffer.st_mode & S_IXUSR);
}

void System::makeFileExecutable(const std::string& filename)
{
	if (!System::isFile(filename))
	{
		LOGE << "Cannot make non-existing file '" << filename << "' executable";
		return;
	}

	struct stat buffer;
	if (::stat(filename.c_str(), &buffer) != 0)
	{
		LOGE << "Failed to stat '" << filename << "'";
		return;
	}

	::chmod(filename.c_str(), buffer.st_mode | S_IRWXU | S_IRWXG);
}

std::string System::getHttpModificationTimeString(const std::string& filename)
{
	struct stat buffer;
	if (::stat(filename.c_str(), &buffer) != 0)
	{
		LOGE << "Failed to stat '" << filename << "'";
		return "";
	}

	if (!S_ISREG(buffer.st_mode))
	{
		LOGE << "Cannot get timestamp of non-file '" << filename << "'";
		return "";
	}

	struct tm* mtime = gmtime(&(buffer.st_mtime));
	char stringbuffer[100];
	strftime(stringbuffer, 100, "%a, %d %b %Y %H:%M:%S GMT", mtime);
	return stringbuffer;
}

void System::purgeFile(const std::string& filename)
{
	if (!isFile(filename))
	{
		// File did not exist in the first place, so no need to purge.
		return;
	}

	System::ofstream(filename, std::ios::binary | std::ios::trunc);
}

void System::unlinkFile(const std::string& filename)
{
	if (!isFile(filename))
	{
		// File did not exist in the first place, so no need to purge.
		return;
	}

	unlink(filename.c_str());
}

void System::moveFile(const std::string& filename, const std::string& dest)
{
	if (!isFile(filename))
	{
		LOGE << "Cannot move non-existing file '" << filename << "'";
		return;
	}

	touchFile(dest);
	if (!isFile(dest))
	{
		LOGE << "Failed to touch '" << dest << "'";
		return;
	}

	unlink(dest.c_str());
	if (isFile(dest))
	{
		LOGE << "Failed to unlink '" << dest << "'";
		return;
	}

	rename(filename.c_str(), dest.c_str());
	if (!isFile(dest))
	{
		LOGE << "Failed to rename file to '" << dest << "'";
	}
}

void System::copyFile(const std::string& filename, const std::string& dest)
{
	if (!isFile(filename))
	{
		LOGE << "Cannot copy non-existing file '" << filename << "'";
		return;
	}

	touchFile(dest);
	if (!isFile(dest))
	{
		LOGE << "Failed to touch '" << dest << "'";
		return;
	}

	std::ifstream source = System::ifstream(filename, std::ios::binary);
	std::ofstream target = System::ofstream(dest,
		std::ios::binary | std::ios::trunc);

	target << source.rdbuf();
}

bool System::isLink(const std::string& filename)
{
	struct stat buffer;
	if (::lstat(filename.c_str(), &buffer) != 0)
	{
		LOGE << "Failed to stat '" << filename << "'";
		return false;
	}

	return S_ISLNK(buffer.st_mode);
}

std::string System::readLink(const std::string& filename)
{
	struct stat buffer;
	if (::lstat(filename.c_str(), &buffer) != 0)
	{
		LOGE << "Failed to stat '" << filename << "'";
		return "";
	}

	if (!S_ISLNK(buffer.st_mode))
	{
		LOGE << "Cannot read non-link '" << filename << "'";
		return "";
	}

	size_t size = buffer.st_size;
	std::vector<char> pathbuffer(size);
	int used = ::readlink(filename.c_str(), pathbuffer.data(), size);
	if (used < 0)
	{
		LOGW << "Failed to read '" << filename << "', or empty";
		return "";
	}

	return std::string(pathbuffer.begin(), pathbuffer.begin() + used);
}

void System::makeLink(const std::string& filename, const char* target)
{
	if (isFile(filename))
	{
		LOGE << "Cannot make non-existing file '" << filename << "' as symlink";
		return;
	}

	if (::symlink(target, filename.c_str()) != 0)
	{
		LOGE << "Failed to symlink '" << filename << "'";
		return;
	}
}

std::string System::absolutePath(const std::string& filename)
{
	char buffer[PATH_MAX];
	const char* result = realpath(filename.c_str(), buffer);
	if (result == nullptr)
	{
		LOGE << "Failed to get absolute path of " << filename;
		return filename;
	}
	return std::string(result);
}

/* ################################## UNIX ################################## */
#else
/* ################################# WINDOWS ################################ */

#include <sys/stat.h>
#include <time.h>
#include <windows.h>
#include <stringapiset.h>
#include <direct.h>

#include "clock.hpp"
#include "keycode.hpp"

#if !defined(S_ISREG) && defined(S_IFMT) && defined(S_IFREG)
#define S_ISREG(m) (((m) & S_IFMT) == S_IFREG)
#endif
#if !defined(S_ISDIR) && defined(S_IFMT) && defined(S_IFDIR)
#define S_ISDIR(m) (((m) & S_IFMT) == S_IFDIR)
#endif


std::wstring System::utf16FromUtf8(const std::string& str)
{
	int num_wchars = MultiByteToWideChar(CP_UTF8, 0, str.c_str(), -1, NULL, 0);
	if (num_wchars <= 0)
	{
		std::cout << "Failed to convert '" << str << "'" << std::endl;
		LOGE << "Failed to convert '" << str << "'";
		return std::wstring();
	}
	std::wstring wstr;
	wstr.resize(num_wchars - 1);
	MultiByteToWideChar(CP_UTF8, 0, str.c_str(), -1, &wstr[0], num_wchars);
	return wstr;
}

FILE* System::fopen(const std::string& filename, const char* mode)
{
	std::wstring wfilename = utf16FromUtf8(filename);
	std::wstring wmode = utf16FromUtf8(mode);
	return _wfopen(wfilename.c_str(), wmode.c_str());
}

std::ifstream System::ifstream(const std::string& filename)
{
	std::wstring wfilename = utf16FromUtf8(filename);
	return std::ifstream(wfilename.c_str());
}

std::ifstream System::ifstream(const std::string& filename,
	std::ios_base::openmode mode)
{
	std::wstring wfilename = utf16FromUtf8(filename);
	return std::ifstream(wfilename.c_str(), mode);
}

std::ofstream System::ofstream(const std::string& filename)
{
	std::wstring wfilename = utf16FromUtf8(filename);
	return std::ofstream(wfilename.c_str());
}

std::ofstream System::ofstream(const std::string& filename,
	std::ios_base::openmode mode)
{
	std::wstring wfilename = utf16FromUtf8(filename);
	return std::ofstream(wfilename.c_str(), mode);
}

void System::touchDirectory(const std::string& dirname)
{
	if (dirname.empty() || dirname == "/")
	{
		LOGE << "Cannot touch dirname '" << dirname << "'";
		return;
	}

	touchParentDirectory(dirname);

	struct stat buffer;
	if (::stat(dirname.c_str(), &buffer) == 0 && S_ISDIR(buffer.st_mode))
	{
		// Directory already exists, no need to touch it.
		return;
	}

	std::wstring wdirname = utf16FromUtf8(dirname);
	::_wmkdir(wdirname.c_str());
}

void System::touchFile(const std::string& filename)
{
	if (filename.empty() || filename == "/")
	{
		LOGE << "Cannot touch filename '" << filename << "'";
		return;
	}

	touchParentDirectory(filename);

	struct stat buffer;
	if (::stat(filename.c_str(), &buffer) == 0 && S_ISREG(buffer.st_mode))
	{
		// File already exists, no need to touch it.
		return;
	}

	std::ofstream file = System::ofstream(filename,
		std::ios::binary | std::ios::app);
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
	if (filename.empty())
	{
		LOGE << "Cannot stat filename '" << filename << "'";
		return false;
	}

	struct stat buffer;
	if (::stat(filename.c_str(), &buffer) != 0)
	{
		// The file does not exist.
		return false;
	}

	return S_ISDIR(buffer.st_mode);
}

bool System::isFile(const std::string& filename)
{
	if (filename.empty() || filename == "/")
	{
		LOGE << "Cannot stat filename '" << filename << "'";
		return false;
	}

	struct stat buffer;
	if (::stat(filename.c_str(), &buffer) != 0)
	{
		// The file does not exist.
		return false;
	}

	return S_ISREG(buffer.st_mode);
}

bool System::isFileNonempty(const std::string& filename)
{
	if (!System::isFile(filename))
	{
		return false;
	}

	std::ifstream file = System::ifstream(filename, std::ios::binary);

	return (file.peek() != std::ifstream::traits_type::eof());
}

bool System::isFileExecutable(const std::string& filename)
{
	if (!System::isFile(filename))
	{
		return false;
	}

	// All files are executable in Windows,
	// but for sanity's sake we look at the extension.
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
	if (::stat(filename.c_str(), &buffer) != 0)
	{
		LOGE << "Failed to stat '" << filename << "'";
		return "";
	}

	if (!S_ISREG(buffer.st_mode))
	{
		LOGE << "Cannot get timestamp of non-file '" << filename << "'";
		return "";
	}

	struct tm* mtime = gmtime(&(buffer.st_mtime));
	char stringbuffer[100];
	strftime(stringbuffer, 100, "%a, %d %b %Y %H:%M:%S GMT", mtime);
	return stringbuffer;
}

void System::purgeFile(const std::string& filename)
{
	if (!isFile(filename))
	{
		// File did not exist in the first place, so no need to purge.
		return;
	}

	std::ofstream file = System::ofstream(filename,
		std::ios::binary | std::ios::trunc);
}

void System::unlinkFile(const std::string& filename)
{
	if (!isFile(filename))
	{
		// File did not exist in the first place, so no need to purge.
		return;
	}

#if SELF_PATCH_ENABLED
	auto timestampMs = EpochClock::milliseconds();
	uint16_t key = rand() % (1 << 16);
	std::string hash = ::keycode(key, timestampMs);

	std::string dest = "downloads/" + filename + "." + hash + ".old";

	std::wstring wdest = utf16FromUtf8(dest);
	std::wstring wfilename = utf16FromUtf8(filename);

	touchFile(dest);
	if (!isFile(dest))
	{
		LOGE << "Failed to touch '" << dest << "'";
		return;
	}

	DeleteFileW(wdest.c_str());
	if (isFile(dest))
	{
		LOGE << "Failed to unlink '" << dest << "'";
		return;
	}

	MoveFileW(wfilename.c_str(), wdest.c_str());
	if (!isFile(dest))
	{
		LOGE << "Failed to move file to '" << dest << "'";
		return;
	}

	DWORD attributes = GetFileAttributesW(wdest.c_str());
	SetFileAttributesW(wdest.c_str(), attributes | FILE_ATTRIBUTE_HIDDEN);

	std::ofstream oldlist = System::ofstream("downloads/old.list",
		std::ofstream::app);
	oldlist << dest << std::endl;
#else
	LOGE << "Unimplemented";
	DEBUG_ASSERT(false);
#endif
}

void System::moveFile(const std::string& filename, const std::string& dest)
{
	if (!isFile(filename))
	{
		LOGE << "Cannot move non-existing file '" << filename << "'";
		return;
	}

	std::wstring wdest = utf16FromUtf8(dest);
	std::wstring wfilename = utf16FromUtf8(filename);

	touchFile(dest);
	if (!isFile(dest))
	{
		LOGE << "Failed to touch '" << dest << "'";
		return;
	}

	DeleteFileW(wdest.c_str());
	if (isFile(dest))
	{
		LOGE << "Failed to unlink '" << dest << "'";
		return;
	}

	MoveFileW(wfilename.c_str(), wdest.c_str());
	if (!isFile(dest))
	{
		LOGE << "Failed to rename file to '" << dest << "'";
	}
}

void System::copyFile(const std::string& filename, const std::string& dest)
{
	if (!isFile(filename))
	{
		LOGE << "Cannot copy non-existing file '" << filename << "'";
		return;
	}

	touchFile(dest);
	if (!isFile(dest))
	{
		LOGE << "Failed to touch '" << dest << "'";
		return;
	}

	std::ifstream source = System::ifstream(filename, std::ios::binary);
	std::ofstream target = System::ofstream(dest,
		std::ios::binary | std::ios::trunc);

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

std::string System::absolutePath(const std::string& filename)
{
	char buffer[_MAX_PATH];
	const char* result = _fullpath(buffer, filename.c_str(), _MAX_PATH);
	if (result == nullptr)
	{
		LOGE << "Failed to get absolute path of " << filename;
		return filename;
	}
	return std::string(result);
}

/* ################################# WINDOWS ################################ */
#endif



static bool doSimpleStorageTest(const std::string& filename)
{
	std::string teststring = "This file was automatically generated.";
	{
		System::touchFile(filename);
		std::ofstream file = System::ofstream(filename,
			std::ofstream::out | std::ofstream::trunc);
		file << teststring << std::endl;
	}
	{
		std::ifstream file = System::ifstream(filename);
		std::string line;
		if (!file.is_open() || !std::getline(file, line)
			|| line != teststring)
		{
			return true;
		}
	}
	return false;
}

bool System::hasStorageIssuesForSelfPatch()
{
	// Do the simple storage test the first time this function is called.
	static const bool has = doSimpleStorageTest("downloads/storage.log");
	return has;
}



inline const char* getVariantName()
{
#ifdef DEVELOPMENT
#ifdef CANDIDATE
	return "epicinium-rc";
#else
	return "epicinium-dev";
#endif
#else
	return "epicinium";
#endif
}

#ifdef PLATFORMDEBIAN
/* ################################# DEBIAN ################################# */
inline std::string getPersistentPath(const char* envname, const char* infix)
{
	std::string path = "";
	if (getenv(envname) != nullptr)
	{
		path = getenv(envname);
	}

	if (path == "/")
	{
		// LogInstaller probably hasn't been called yet.
		std::cerr << "Ignoring " << envname << "=" << path << std::endl;
		path = "";
	}

	if (path.empty())
	{
		if (getenv("HOME") == nullptr)
		{
			// LogInstaller probably hasn't been called yet.
			std::cerr << "No HOME dir defined." << std::endl;
			return "";
		}

		path = getenv("HOME");
		if (path.empty() || path == "/")
		{
			// LogInstaller probably hasn't been called yet.
			std::cerr << "Invalid HOME dir: " << path << std::endl;
			return "";
		}

		if (path.back() != '/')
		{
			path += "/";
		}
		path = path + infix;
	}

	if (path.back() != '/')
	{
		path += "/";
	}
	path += getVariantName();
	path += "/";

	return path;
}

std::string System::getPersistentConfigRoot()
{
	return getPersistentPath("XDG_CONFIG_HOME", ".config/");
}

std::string System::getPersistentDataRoot()
{
	return getPersistentPath("XDG_DATA_HOME", ".local/share/");
}

std::string System::getPersistentCacheRoot()
{
	return getPersistentPath("XDG_CACHE_HOME", ".cache/");
}
/* ################################# DEBIAN ################################# */
#endif
#ifdef PLATFORMOSX
/* ################################## OSX ################################### */
#include <limits.h>
#include <sysdir.h>

inline std::string getPersistentPath(sysdir_search_path_directory_t dir)
{
	auto state = sysdir_start_search_path_enumeration(dir, SYSDIR_DOMAIN_MASK_USER);
	if (state == 0)
	{
		// LogInstaller probably hasn't been called yet.
		std::cout << "Failed to get persistent path" << std::endl;
		return "";
	}
	char buffer[PATH_MAX];
	sysdir_get_next_search_path_enumeration(state, buffer);
	std::string path = buffer;
	if (path.empty())
	{
		// LogInstaller probably hasn't been called yet.
		std::cout << "Failed to get persistent path,"
			" returned empty string" << std::endl;
		return "";
	}

	if (path.size() > 2 && path.substr(0, 2) == "~/")
	{
		if (getenv("HOME") != nullptr)
		{
			std::string home = getenv("HOME");
			if (home.empty())
			{
				// LogInstaller probably hasn't been called yet.
				std::cout << "Failed to get HOME,"
					" returned empty string" << std::endl;
			}
			else
			{
				if (home.back() != '/')
				{
					home += "/";
				}
				path = home + path.substr(2);
			}
		}
		else
		{
			// LogInstaller probably hasn't been called yet.
			std::cout << "Failed to get HOME,"
				" using literal ~" << std::endl;
		}
	}

	if (path.back() != '/')
	{
		path += "/";
	}
	path += std::string("coop.abunchofhacks.");
	path += getVariantName();
	return path;
}

std::string System::getPersistentConfigRoot()
{
	return getPersistentPath(SYSDIR_DIRECTORY_APPLICATION_SUPPORT);
}

std::string System::getPersistentDataRoot()
{
	return getPersistentPath(SYSDIR_DIRECTORY_APPLICATION_SUPPORT);
}

std::string System::getPersistentCacheRoot()
{
	return getPersistentPath(SYSDIR_DIRECTORY_CACHES);
}
/* ################################## OSX ################################### */
#endif
#ifdef PLATFORMWINDOWS
/* ################################# WINDOWS ################################ */
#include <shlobj.h>

inline std::string utf8FromUtf16(const std::wstring& wstr)
{
	int len = WideCharToMultiByte(CP_UTF8, WC_NO_BEST_FIT_CHARS,
		wstr.c_str(), -1, NULL, 0, NULL, NULL);
	if (len <= 0)
	{
		// LogInstaller probably hasn't been called yet.
		std::cout << "Failed to convert" << std::endl;
		return "";
	}
	std::string str;
	str.resize(len - 1);
	WideCharToMultiByte(CP_UTF8, WC_NO_BEST_FIT_CHARS,
		wstr.c_str(), -1, &str[0], len, NULL, NULL);
	return str;
}

inline std::string getPersistentPath()
{
	std::wstring wsubname = System::utf16FromUtf8(getVariantName());

	wchar_t buffer[MAX_PATH];
	HRESULT result = SHGetFolderPathAndSubDirW(nullptr,
		CSIDL_LOCAL_APPDATA | CSIDL_FLAG_CREATE | CSIDL_FLAG_DONT_UNEXPAND,
		nullptr, SHGFP_TYPE_CURRENT, wsubname.c_str(), buffer);
	if (result != S_OK)
	{
		// LogInstaller probably hasn't been called yet.
		std::cout << "Failed to get persistent root, error code: "
			<< std::hex << std::showbase << result << std::dec
			<< std::endl;
		return "";
	}

	std::string path = utf8FromUtf16(buffer);
	if (path.empty())
	{
		// LogInstaller probably hasn't been called yet.
		std::cout << "Failed to get persistent root, error code: "
			" returned empty string" << std::endl;
		return "";
	}

	if (path.back() == '\\')
	{
		path += getVariantName();
	}

	if (path.back() != '/')
	{
		path += "/";
	}
	return path;
}

std::string System::getPersistentConfigRoot()
{
	return getPersistentPath();
}

std::string System::getPersistentDataRoot()
{
	return getPersistentPath();
}

std::string System::getPersistentCacheRoot()
{
	return getPersistentPath();
}
/* ################################# WINDOWS ################################ */
#endif
