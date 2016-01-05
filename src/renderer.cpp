#include "renderer.h"

#include <cmath>

#define SCALE 25

ALLEGRO_DISPLAY* display;
ALLEGRO_FONT* font;

ALLEGRO_COLOR Renderer::green;
ALLEGRO_COLOR Renderer::red;
ALLEGRO_COLOR Renderer::white;
ALLEGRO_COLOR Renderer::black;
ALLEGRO_COLOR Renderer::blue;

void Renderer::init()
{
	al_set_new_display_flags(ALLEGRO_RESIZABLE);
	display = al_create_display(800, 600);
	al_init_font_addon();
	al_init_ttf_addon();
	al_init_primitives_addon();
	al_set_target_backbuffer(display);
	font = al_load_ttf_font("res/LiberationSans-Regular.ttf", 14, 0);

	green = al_map_rgba(0, 255, 0, 255);
	red = al_map_rgba(255, 0, 0, 255);
	blue = al_map_rgba(0, 0, 255, 255);
	white = al_map_rgba(255, 255, 255, 255);
	black = al_map_rgba(0, 0, 0, 255);

}
void Renderer::deinit()
{
	al_destroy_display(display);
	al_destroy_font(font);
}

ALLEGRO_DISPLAY* Renderer::getDisplay()
{
	return display;
}

void Renderer::drawTable()
{
	for(int i= -100; i < 100; i+=1)
	{
		Coordinates start = TransformToScreenCoordinates(Coordinates(i, -100));
		Coordinates end = TransformToScreenCoordinates(Coordinates(i, 100));
		al_draw_line(start.x, start.y, end.x, end.y, black, 0);
	}
	for(int i= -100; i < 100; i+=1)
	{
		Coordinates start = TransformToScreenCoordinates(Coordinates(-100, i));
		Coordinates end = TransformToScreenCoordinates(Coordinates(100, i));
		al_draw_line(start.x, start.y, end.x, end.y, black, 0);
	}
}

Coordinates Renderer::TransformToScreenCoordinates(const Coordinates coordinates)
{
	const int width = al_get_display_width(display);
	const int height = al_get_display_height(display);
	Coordinates newCoords(width/2, height/2);
	newCoords.x += coordinates.x * SCALE;
	newCoords.y += coordinates.y * SCALE;
	return newCoords;
}

Coordinates Renderer::TransformToGameCoordinates(const Coordinates coordinates)
{
	Coordinates newCoords = coordinates;
	const int width = al_get_display_width(display);
	const int height = al_get_display_height(display);

	newCoords.x -= width / 2;
	newCoords.y -= height / 2;

	if(newCoords.x > 0)
	{
		newCoords.x = (newCoords.x + (SCALE/2)) / SCALE;
	}
	else
	{
		newCoords.x = (newCoords.x - (SCALE/2)) / SCALE;
	}
	if(newCoords.y > 0)
	{
		newCoords.y = (newCoords.y + (SCALE/2)) / SCALE;
	}
	else
	{
		newCoords.y = (newCoords.y - (SCALE/2)) / SCALE;
	}

	return newCoords;
}

void Renderer::drawCross(const Coordinates coordinates, const ALLEGRO_COLOR* color)
{
	Coordinates screenCoords = TransformToScreenCoordinates(coordinates);
	al_draw_line(screenCoords.x - 4, screenCoords.y + 4, screenCoords.x + 4, screenCoords.y - 4, *color, 2);
	al_draw_line(screenCoords.x - 4, screenCoords.y - 4, screenCoords.x + 4, screenCoords.y + 4, *color, 2);
}

void Renderer::drawText(const Coordinates coordinates, const ALLEGRO_COLOR* color, std::string text)
{
	al_draw_text(font, *color, coordinates.x, coordinates.y, 0, text.c_str());
}

ALLEGRO_FONT* Renderer::getFont()
{
	return font;
}
