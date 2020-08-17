#include "position.hpp"
#include "source.hpp"


Position::Position(const Json::Value& json) :
	row(json["row"].asInt()),
	col(json["col"].asInt())
{}

std::ostream& operator<<(std::ostream& os, const Position& pos)
{
	return os << "{"
		"\"row\":" << ((int) pos.row) << ""
		","
		"\"col\":" << ((int) pos.col) << ""
		"}";
}
