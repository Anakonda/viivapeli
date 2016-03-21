
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
	Coordinates checkLocation = this->location;
	if(checkLocation.x < 0)
	{
		checkLocation.x = al_get_display_width(Renderer::getDisplay()) + this->location.x;
	}
	if(checkLocation.y < 0)
	{
		checkLocation.y = al_get_display_height(Renderer::getDisplay()) + this->location.y;
	}
	return clickPos.x > checkLocation.x && clickPos.y > checkLocation.y && clickPos.x < (checkLocation + this->size).x && clickPos.y < (checkLocation + this->size).y;
}
