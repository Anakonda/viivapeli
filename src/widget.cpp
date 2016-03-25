
#include "widget.h"

Widget::Widget(Coordinates location, std::pair<Alignment, Alignment> alignment, Coordinates size)
{
	this->alignment = alignment;
	this->location = location;
	this->size = size;
	this->resize(Coordinates(al_get_display_width(Renderer::getDisplay()), al_get_display_height(Renderer::getDisplay())));
}

Widget::~Widget()
{

}

bool Widget::checkHit(Coordinates clickPos)
{
	Coordinates checkLocation = this->realLocation;
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

void Widget::resize(Coordinates newSize)
{
	this->realLocation = this->location;
	if(this->alignment.first == Alignment::CENTER)
	{
		this->realLocation.x = newSize.x / 2 + this->location.x;
	}
	else if(this->alignment.first == Alignment::RIGHT)
	{
		this->realLocation.x = newSize.x + this->location.x;
	}
	if(this->alignment.second == Alignment::CENTER)
	{
		this->realLocation.y = newSize.y / 2 + this->location.y;
	}
	else if(this->alignment.second == Alignment::BOTTOM)
	{
		this->realLocation.y = newSize.y + this->location.y;
	}
}
