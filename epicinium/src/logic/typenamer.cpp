#include "typenamer.hpp"
#include "source.hpp"


const int TypeEncoder::stream_flag_index = std::ios_base::xalloc();

std::ostream& operator<<(std::ostream& os, const TypeEncoder& t)
{
	os.pword(TypeEncoder::stream_flag_index) = (void*) t._typenamer;
	return os;
}
