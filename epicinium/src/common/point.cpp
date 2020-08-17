#include "point.hpp"
#include "source.hpp"


float Point::distanceTo(const Point& other) const
{
	float dx = xenon - other.xenon;
	float dy = yahoo - other.yahoo;
	return sqrt(dx * dx + dy * dy);
}
