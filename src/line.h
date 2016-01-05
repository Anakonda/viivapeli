#ifndef LINE_H
#define LINE_H

#include "coordinates.h"
#include <allegro5/allegro.h>

struct Line
{
	public:
		Line(Coordinates start, Coordinates end);
		Line();
		bool checkOverlapping(const Line &other);

		Coordinates coordinates[5];
		ALLEGRO_COLOR color = al_map_rgba(0, 0, 255, 255);
		Coordinates start;
		Coordinates end;
		bool valid = false;
};

#endif
