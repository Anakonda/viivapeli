#include "line.h"

#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

#include <string>

namespace Renderer
{
	extern ALLEGRO_COLOR green;
	extern ALLEGRO_COLOR red;
	extern ALLEGRO_COLOR white;
	extern ALLEGRO_COLOR black;
	extern ALLEGRO_COLOR blue;
	extern ALLEGRO_COLOR purple;
	extern ALLEGRO_COLOR cyan;

	void init();
	void deinit();
	ALLEGRO_DISPLAY* getDisplay();
	void drawTable();

	ALLEGRO_FONT* getFont();

	void drawCross(const Coordinates coordinates, const ALLEGRO_COLOR* color);

	void drawText(const Coordinates coordinates, const ALLEGRO_COLOR* color, const std::string text);

	Coordinates TransformToScreenCoordinates(const Coordinates coordinates);
	Coordinates TransformToGameCoordinates(const Coordinates coordinates);
}
