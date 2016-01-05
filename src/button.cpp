
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
	al_draw_filled_rectangle(location.x, location.y, location.x + size.x, location.y + size.y, *this->backgroundColor);
	al_draw_rectangle(location.x, location.y, location.x + size.x, location.y + size.y, Renderer::black, 1);
	Renderer::drawText(this->location + Coordinates(2, 2), this->textColor, this->text);
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
