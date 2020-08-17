#include "cell.hpp"
#include "source.hpp"


std::ostream& operator<<(std::ostream& os, Cell index)
{
	return os << "[" << index.ix() << " 0x" << std::hex
		<< std::setfill('0') << std::setw(2) << int(index._rows)
		<< std::setfill('0') << std::setw(2) << int(index._cols)
		<< std::setfill('0') << std::setw(4) << int(index._ix)
		<< std::dec << "]";
}
