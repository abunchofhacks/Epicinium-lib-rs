#pragma once
#include "header.hpp"

#include <dlfcn.h>


template <class T>
class LibLoader
{
private:
	std::string _pathToLib;
	void* _handle;
	void* _alloc;

public:
	LibLoader(LibLoader&& that) :
		_pathToLib(that._pathToLib),
		_handle(that._handle),
		_alloc(that._alloc)
	{
		that._handle = nullptr;
		that._alloc = nullptr;
	}

	LibLoader(const std::string& path) :
		_pathToLib(path),
		_handle(dlopen(_pathToLib.c_str(), RTLD_LAZY | RTLD_DEEPBIND)),
		_alloc(_handle ? dlsym(_handle, "allocate") : nullptr)
	{
		if (_handle == nullptr)
		{
			LOGE << "Failed to load library '" << _pathToLib << "': "
				<< dlerror();
		}
		// Check dlsym errors in opposite order; the errors overwrite eachother.
		else if (_alloc == nullptr)
		{
			LOGE << "Failed to load 'allocate'"
				<< " from library '" << _pathToLib << "': "
				<< dlerror();
			if (!dlclose(_handle))
			{
				LOGE << "Failed to unload library '" << _pathToLib << "': "
					<< dlerror();
			}
		}
		else
		{
			LOGI << "Library '" << _pathToLib << "' loaded";

			void* setup = dlsym(_handle, "setup");
			if (setup)
			{
				auto setupFunc = (void(*)(int, const char* const [])) setup;
				std::string arg_logname = "--logname=" + ::sanitize(_pathToLib);
				const char* const args[] = {
					_pathToLib.c_str(), // like main(), first arg is path
					arg_logname.c_str(),
					"--logrollback=2",
				};
				setupFunc(array_size(args), args);

				LOGI << "Library '" << _pathToLib << "' set up";
			}
		}
	}

	LibLoader(const LibLoader&) = delete;
	LibLoader& operator=(const LibLoader&) = delete;
	LibLoader& operator=(LibLoader&&) = delete;

	~LibLoader()
	{
		if (_handle != nullptr)
		{
			if (dlclose(_handle))
			{
				LOGI << "Library '" << _pathToLib << "' unloaded";
			}
			else
			{
				LOGE << "Failed to unload library '" << _pathToLib << "': "
					<< dlerror();
			}
		}
	}

public:
	explicit operator bool() const
	{
		return (_handle != nullptr);
	}

	const std::string& pathToLib() const
	{
		return _pathToLib;
	}

	template <typename ...As>
	T* instantiate(As... args)
	{
		if (!_alloc) return nullptr;

		auto allocFunc = (T*(*)(As...)) _alloc;
		return allocFunc(args...);
	}
};
