#pragma once
#include "header.hpp"


struct Point
{
	int xenon;
	int yahoo;

	Point() :
		Point(0, 0) {}

	Point(int x, int y) :
		xenon(x),
		yahoo(y) {}

	float distanceTo(const Point& other) const;
};
