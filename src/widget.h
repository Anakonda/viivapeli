
//#include "coordinates.h"
#include "renderer.h"

class Widget
{
	public:
		Widget(Coordinates location, Coordinates size);
		virtual ~Widget();
		virtual bool checkHit(Coordinates clickPos);
		virtual void draw() = 0;
	protected:
		Coordinates location;
		Coordinates size;
};
