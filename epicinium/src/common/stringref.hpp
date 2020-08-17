#pragma once
#include "header.hpp"

#include <cstring>


struct stringref
{
private:
	const char* const _data;
	const size_t _size;

public:
	template <size_t N>
	constexpr stringref(const char (&lit)[N]) :
		_data(lit),
		_size(N)
	{}

	explicit stringref(const char* raw) :
		_data(raw),
		_size(strlen(raw) + 1)
	{}

	stringref(const std::string& str) :
		_data(str.c_str()),
		_size(str.size() + 1)
	{}

	stringref(const stringref&) = default;
	stringref(stringref&&) = default;
	stringref& operator=(const stringref&) = delete;
	stringref& operator=(stringref&&) = delete;
	~stringref() = default;

	friend bool operator==(const stringref& a, const stringref& b)
	{
		return (a._size == b._size && strcmp(a._data, b._data) == 0);
	}

	friend bool operator!=(const stringref& a, const stringref& b)
	{
		return (a._size != b._size || strcmp(a._data, b._data) != 0);
	}

	friend bool strncmp(stringref a, stringref b, size_t n)
	{
		return strncmp(a._data, b._data, n);
	}

	std::string str() const
	{
		return std::string(_data);
	}

	friend std::ostream& operator<<(std::ostream& os, stringref str);
};
