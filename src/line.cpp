#include "line.h"


Line::Line(Coordinates start, Coordinates end)
{
	this->start = start;
	this->end = end;

	char xDifference = 0;
	char yDifference = 0;
	if(start.x - end.x == 4)
	{
		xDifference = -1;
	}
	else if(start.x - end.x == -4)
	{
		xDifference = 1;
	}
	if(start.y - end.y == 4)
	{
		yDifference = -1;
	}
	else if(start.y - end.y == -4)
	{
		yDifference = 1;
	}

	this->coordinates[0] = start;
	this->coordinates[1] = start + Coordinates(xDifference * 1, yDifference * 1);
	this->coordinates[2] = start + Coordinates(xDifference * 2, yDifference * 2);
	this->coordinates[3] = start + Coordinates(xDifference * 3, yDifference * 3);
	this->coordinates[4] = start + Coordinates(xDifference * 4, yDifference * 4);
	if(this->coordinates[4] == this->end && this->start != this->end)
	{
		this->valid = true;
	}
}

Line::Line()
{

}

bool Line::checkOverlapping(const Line &other)
{
	unsigned char commonPoints = 0;
	for(auto &myPoint : this->coordinates)
	{
		for(auto &otherPoint : other.coordinates)
		{
			if(myPoint == otherPoint)
			{
				commonPoints++;
			}
		}
	}
	return commonPoints > 1;
}
