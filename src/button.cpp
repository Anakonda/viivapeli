
#include "button.h"

Button::Button(Coordinates location, Coordinates size, ALLEGRO_COLOR* backgroundColor, ALLEGRO_COLOR* textColor, std::string text, void (*callback)(Widget*))
	: Widget(location, size)
{
	this->backgroundColor = backgroundColor;
	this->textColor = textColor;
	this->text = text;

	this->callback = callback;
}

Button::~Button()
{

}

void Button::draw()
{
	Coordinates drawLocation = this->location;
	if(drawLocation.x < 0)
	{
		drawLocation.x = al_get_display_width(Renderer::getDisplay()) + this->location.x;
	}
	if(drawLocation.y < 0)
	{
		drawLocation.y = al_get_display_height(Renderer::getDisplay()) + this->location.y;
	}
	al_draw_filled_rectangle(drawLocation.x, drawLocation.y, drawLocation.x + size.x, drawLocation.y + size.y, *this->backgroundColor);
	al_draw_rectangle(drawLocation.x, drawLocation.y, drawLocation.x + size.x, drawLocation.y + size.y, Renderer::black, 1);
	Renderer::drawText(drawLocation + Coordinates(2, 2), this->textColor, this->text);
}

bool Button::checkHit(Coordinates clickPos)
{
	if(Widget::checkHit(clickPos))
	{
		this->callback(this);
		return true;
	}
	return false;
}
