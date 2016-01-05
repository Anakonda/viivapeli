
#include "widget.h"

#include <allegro5/allegro_primitives.h>

#include <string>

class Button : public Widget
{
	public:
		Button(Coordinates location, Coordinates size, ALLEGRO_COLOR* backgroundColor, ALLEGRO_COLOR* textColor, std::string text, void (*callback)(Widget*));
		virtual ~Button();
		virtual void draw() override;
		virtual bool checkHit(Coordinates clickPos) override;

		ALLEGRO_COLOR* backgroundColor;
		ALLEGRO_COLOR* textColor;
		std::string text;

		void (*callback)(Widget*);
};
