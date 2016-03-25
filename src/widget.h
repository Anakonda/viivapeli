
//#include "coordinates.h"
#include "renderer.h"

enum class Alignment
{
	LEFT,
	RIGHT,
	CENTER,
	TOP,
	BOTTOM
};


class Widget
{
	public:
		Widget(Coordinates location, std::pair<Alignment, Alignment> alignment, Coordinates size);
		virtual ~Widget();
		virtual bool checkHit(Coordinates clickPos);
		virtual void draw() = 0;
		virtual void resize(Coordinates newSize);
	protected:
		std::pair<Alignment, Alignment> alignment;
		Coordinates location;
		Coordinates size;
		Coordinates realLocation;
};
