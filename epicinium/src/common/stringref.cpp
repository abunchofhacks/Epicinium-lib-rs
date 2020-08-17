#include "stringref.hpp"
#include "source.hpp"


std::ostream& operator<<(std::ostream& os, stringref str)
{
	return os << str._data;
}
