#include <vector>
#include "renderer.h"

std::unordered_set<Coordinates> validPoints;
std::unordered_set<Coordinates> startPoints;
std::vector<Line> lines;

Coordinates tempPoint;
bool makingLine = false;

unsigned char extraPoints = 0;


int main(int argc, char **argv)
{

	al_init();
	al_install_mouse();

	Renderer::init();

	ALLEGRO_EVENT_QUEUE *event_queue = al_create_event_queue();

	al_register_event_source(event_queue, al_get_display_event_source(Renderer::getDisplay()));
	al_register_event_source(event_queue, al_get_mouse_event_source());

	{
		validPoints.insert(Coordinates(-2,-5));
		validPoints.insert(Coordinates(-1,-5));
		validPoints.insert(Coordinates( 0,-5));
		validPoints.insert(Coordinates( 1,-5));
		validPoints.insert(Coordinates( 1,-4));
		validPoints.insert(Coordinates( 1,-3));
		validPoints.insert(Coordinates( 1,-2));
		validPoints.insert(Coordinates( 2,-2));
		validPoints.insert(Coordinates( 3,-2));
		validPoints.insert(Coordinates( 4,-2));
		validPoints.insert(Coordinates( 4,-1));
		validPoints.insert(Coordinates( 4, 0));
		validPoints.insert(Coordinates( 4, 1));
		validPoints.insert(Coordinates( 3, 1));
		validPoints.insert(Coordinates( 2, 1));
		validPoints.insert(Coordinates( 1, 1));
		validPoints.insert(Coordinates( 1, 2));
		validPoints.insert(Coordinates( 1, 3));
		validPoints.insert(Coordinates( 1, 4));
		validPoints.insert(Coordinates( 0, 4));
		validPoints.insert(Coordinates(-1, 4));
		validPoints.insert(Coordinates(-2, 4));
		validPoints.insert(Coordinates(-2, 3));
		validPoints.insert(Coordinates(-2, 2));
		validPoints.insert(Coordinates(-2, 1));
		validPoints.insert(Coordinates(-3, 1));
		validPoints.insert(Coordinates(-4, 1));
		validPoints.insert(Coordinates(-5, 1));
		validPoints.insert(Coordinates(-5, 0));
		validPoints.insert(Coordinates(-5,-1));
		validPoints.insert(Coordinates(-5,-2));
		validPoints.insert(Coordinates(-4,-2));
		validPoints.insert(Coordinates(-3,-2));
		validPoints.insert(Coordinates(-2,-2));
		validPoints.insert(Coordinates(-2,-3));
		validPoints.insert(Coordinates(-2,-4));
	}
	startPoints = validPoints;

	bool running = true;
	while (running)
	{
		ALLEGRO_EVENT event;
		while(al_get_next_event(event_queue, &event))
		{
			if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
			{
				running = false;
				break;
			}
			else if(event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
			{
				if(event.mouse.button == 1)
				{
					if(!makingLine)
					{
						makingLine = true;
						tempPoint = Renderer::TransformToGameCoordinates(Coordinates(event.mouse.x, event.mouse.y));
					}
					else
					{
						Line newLine(tempPoint, Renderer::TransformToGameCoordinates(Coordinates(event.mouse.x, event.mouse.y)));
						char existingPoints = 0;
						for(auto point : newLine.coordinates)
						{
							if(validPoints.count(point) > 0)
							{
								existingPoints += 1;
							}
						}
						if(existingPoints < 4)
						{
							makingLine = false;
							continue;
						}
						else if(existingPoints == 5)
						{
							extraPoints += 1;
						}

						bool valid = true;
						for(auto &line : lines)
						{
							char samePoints = 0;
							for(auto &point : line.coordinates)
							{
								for(auto &newPoint : newLine.coordinates)
								{
									if(point == newPoint)
									{
										samePoints += 1;
									}
								}
							}
							if(samePoints > 1)
							{
								valid = false;
								break;
							}
						}
						if(!valid)
						{
							makingLine = false;
							continue;
						}

						if(newLine.valid)
						{
							lines.push_back(newLine);
							for(auto point : newLine.coordinates)
							{
								validPoints.insert(point);
							}
						}
						makingLine = false;
					}
				}
			}
		}
		al_clear_to_color(al_map_rgb_f(1, 1, 1));
		// Begin render
		al_hold_bitmap_drawing(true);

		Renderer::drawTable();

		for(auto &point : startPoints)
		{
			Renderer::drawCross(point, &Renderer::red);
		}
		for(auto &line : lines)
		{
			Coordinates start = Renderer::TransformToScreenCoordinates(line.start);
			Coordinates end = Renderer::TransformToScreenCoordinates(line.end);
			al_draw_line(start.x, start.y, end.x, end.y, line.color, 2);
		}

		if(makingLine)
		{
			Renderer::drawCross(tempPoint, &Renderer::green);
		}

		Renderer::drawText(Coordinates(5, 5), &Renderer::black, std::to_string(lines.size()));

		// Finish render
		al_hold_bitmap_drawing(false);

		// Draw the rendering
		al_flip_display();
	}



	return 0;

}
