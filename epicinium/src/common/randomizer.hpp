#pragma once
#include "header.hpp"


template <class T>
class Randomizer
{
public:
	explicit Randomizer(size_t size = 0) :
		shuffle(false)
	{
		options.reserve(size);
	}

	void push(T t)
	{
		options.push_back(t);
		shuffle = true;
	}

	void select(size_t index)
	{
		if (index + 1 < options.size())
		{
			std::rotate(options.begin() + index,
				options.begin() + index + 1,
				options.end());
		}
		shuffle = false;
	}

	const T& inspect(size_t index) const
	{
		return options[index];
	}

	const T& peek() const
	{
		return options.back();
	}

	T pop()
	{
		if (shuffle)
		{
			std::random_shuffle(options.begin(), options.end());
			shuffle = false;
		}
		T t = options.back();
		options.pop_back();
		return t;
	}

	void clear()
	{
		options.clear();
	}

	size_t count() const
	{
		return options.size();
	}

	bool empty() const
	{
		return options.empty();
	}

	explicit operator bool() const
	{
		return !empty();
	}

private:
	bool shuffle;
	std::vector<T> options;
};
