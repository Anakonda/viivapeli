#include "coordinates.h"

Coordinates::Coordinates(int x, int y)
{
	this->x = x;
	this->y = y;
}

std::ostream& operator<<(std::ostream &output, const Coordinates &vector) {
	output << "(" <<  vector.x << ", " << vector.y << ")";
	return output;
}
