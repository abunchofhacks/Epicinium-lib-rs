#pragma once
#include "header.hpp"

class SizeIter
{
public:
	typedef SizeIter self_type;
	typedef size_t value_type;
	typedef size_t& reference;
	typedef size_t* pointer;
	typedef std::forward_iterator_tag iterator_category;
	typedef size_t difference_type;

	explicit SizeIter(size_t i) : _i(i) {}

private:
	size_t _i;

public:
	SizeIter& operator++() { ++_i; return *this; }
	SizeIter operator++(int /**/) { return SizeIter(_i++); }
	size_t operator*() const { return _i; }
	const size_t* operator->() const { return &_i; }
	friend void swap(SizeIter& a, SizeIter& b) { std::swap(a._i, b._i); }
	friend bool operator==(const SizeIter& a, const SizeIter& b) { return a._i == b._i; }
	friend bool operator!=(const SizeIter& a, const SizeIter& b) { return a._i != b._i; }
};
