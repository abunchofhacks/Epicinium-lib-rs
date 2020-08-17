#pragma once
#include "header.hpp"

#include "tiletype.hpp"
#include "unittype.hpp"
#include "typeword.hpp"


template <typename T>
class Enumerator
{
public:
	explicit Enumerator(uint16_t i) : _i(i) {}
	Enumerator(uint8_t i, uint8_t end) : _i((end << 8) | i) {}

private:
	uint16_t _i;

public:
	Enumerator& operator++() { ++_i; return *this; }
	Enumerator operator++(int /**/) { return Enumerator(_i++); }
	T operator*() const { return static_cast<T>(_i & 0xFF); }
	friend bool operator==(const Enumerator& a, const Enumerator& b)
	{
		return a._i == b._i;
	}
	friend bool operator!=(const Enumerator& a, const Enumerator& b)
	{
		return a._i != b._i;
	}
	Enumerator begin() const { return Enumerator(0, _i >> 8); }
	Enumerator end() const { return Enumerator(_i >> 8, _i >> 8); }
};

class TypeNamer
{
protected:
	uint8_t _tiletype_max;
	uint8_t _unittype_max;
	std::array<TypeWord, TILETYPE_SIZE> _tiletypes;
	std::array<TypeWord, UNITTYPE_SIZE> _unittypes;

public:
	TileType tiletype(const char* word) const
	{
		// Note that _tiletypes[0] is always "none".
		for (size_t i = 1; i <= _tiletype_max; i++)
		{
			if (_tiletypes[i] == word) return (TileType) i;
		}
		return TileType::NONE;
	}

	UnitType unittype(const char* word) const
	{
		// Note that _unittypes[0] is always "none".
		for (size_t i = 1; i <= _unittype_max; i++)
		{
			if (_unittypes[i] == word) return (UnitType) i;
		}
		return UnitType::NONE;
	}

	const TypeWord& typeword(const TileType& x) const
	{
		return _tiletypes[(size_t) x];
	}

	const TypeWord& typeword(const UnitType& x) const
	{
		return _unittypes[(size_t) x];
	}

	uint8_t tiletype_max() const { return _tiletype_max; }
	uint8_t unittype_max() const { return _unittype_max; }

	Enumerator<TileType> tiletypes() const
	{
		return {(uint8_t) 1, (uint8_t) (_tiletype_max + 1)};
	}
	Enumerator<UnitType> unittypes() const
	{
		return {(uint8_t) 1, (uint8_t) (_unittype_max + 1)};
	}
};

class TypeEncoder
{
public:
	static const int stream_flag_index;

	explicit TypeEncoder(const TypeNamer* typenamer) :
		_typenamer(typenamer)
	{}

private:
	const TypeNamer* const _typenamer;

	friend std::ostream& operator<<(std::ostream& os, const TypeEncoder& t);
};
