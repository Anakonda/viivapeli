
#include "widget.h"

Widget::Widget(Coordinates location, Coordinates size)
{
	this->location = location;
	this->size = size;
}

Widget::~Widget()
{

}

bool Widget::checkHit(Coordinates clickPos)
{
	return clickPos.x > this->location.x && clickPos.y > this->location.y && clickPos.x < (this->location + this->size).x && clickPos.y < (this->location + this->size).y;
}
