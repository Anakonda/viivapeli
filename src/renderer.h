#include "line.h"

#include <allegro5/allegro_primitives.h>

#include <string>

namespace Renderer
{
	extern ALLEGRO_COLOR green;
	extern ALLEGRO_COLOR red;
	extern ALLEGRO_COLOR white;
	extern ALLEGRO_COLOR black;
	extern ALLEGRO_COLOR blue;
	void init();
	void deinit();
	ALLEGRO_DISPLAY* getDisplay();
	void drawTable();

	void drawCross(const Coordinates coordinates, const ALLEGRO_COLOR* color);

	void drawText(const Coordinates coordinates, const ALLEGRO_COLOR* color, const std::string text);

	Coordinates TransformToScreenCoordinates(const Coordinates coordinates);
	Coordinates TransformToGameCoordinates(const Coordinates coordinates);
}
