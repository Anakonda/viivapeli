
#include "game.h"

#include <iostream>

std::vector<Widget*> widgets;
Button* crossPlaceButton;

std::unordered_set<Coordinates> validPoints;
std::unordered_set<Coordinates> startPoints;
std::vector<Line> lines;

Coordinates tempPoint;
bool makingLine = false;
bool placingCross = false;

unsigned char extraPoints = 0;

bool gameRunning;

bool stayOpen = true;

Line possibleMove;

ALLEGRO_EVENT_QUEUE *eventQueue;

void placeCross(Widget*)
{
	placingCross = true;
}

void close(Widget*)
{
	stayOpen = true;
	gameRunning = false;
}

void removeWidget(Widget* widget)
{
	widgets.erase(std::find(widgets.begin(), widgets.end(), widget));
	delete widget;
}

void checkForPossibleMoves()
{
	bool moveFound = false;
	for(auto &point : validPoints)
	{
		std::vector<Coordinates> pointsToCheck;
		pointsToCheck.push_back(point + Coordinates( 0,  4));
		pointsToCheck.push_back(point + Coordinates( 4,  4));
		pointsToCheck.push_back(point + Coordinates( 4,  0));
		pointsToCheck.push_back(point + Coordinates( 4, -4));
		pointsToCheck.push_back(point + Coordinates( 0, -4));
		pointsToCheck.push_back(point + Coordinates(-4, -4));
		pointsToCheck.push_back(point + Coordinates(-4,  0));
		pointsToCheck.push_back(point + Coordinates(-4,  4));

		for(auto &pointToCheck : pointsToCheck)
		{
			Line tempLine = Line(point, pointToCheck);
			bool overlapping  = false;
			for(auto &line : lines)
			{
				if(tempLine.checkOverlapping(line))
				{
					overlapping = true;
					break;
				}
			}
			if(!overlapping)
			{
				unsigned char existingPoints = 0;
				for(auto &coordinate : tempLine.coordinates)
				{
					if(validPoints.count(coordinate) > 0)
					{
						existingPoints++;
					}
				}
				if(existingPoints > 3)
				{
					possibleMove = tempLine;
					possibleMove.color = Renderer::purple;
					moveFound = true;
					break;
				}

			}
			if(moveFound)
			{
				break;
			}
		}
		if(moveFound)
		{
			break;
		}
	}
	if(!moveFound)
	{
		const int width = al_get_display_width(Renderer::getDisplay());
		const int height = al_get_display_height(Renderer::getDisplay());
		widgets.push_back(new Button(Coordinates(width / 2 - 1+0, height / 2 - 10), Coordinates(200, 20), &Renderer::white, &Renderer::red, std::string("No more valid moves."), close));
	}
}


bool game()
{
	gameRunning = true;

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

	{
		const int width = al_get_display_width(Renderer::getDisplay());
		const int height = al_get_display_height(Renderer::getDisplay());
		widgets.push_back(new Button(Coordinates(width - 100, 0), Coordinates(100, 25), &Renderer::white, &Renderer::red, std::string("Close"), close));
	}

	while (gameRunning)
	{
		ALLEGRO_EVENT event;
		while(al_get_next_event(eventQueue, &event))
		{
			if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
			{
				stayOpen = false;
				gameRunning = false;
				break;
			}
			else if(event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
			{
				if(event.mouse.button == 1)
				{
					bool hitUI = false;
					Coordinates mouse(event.mouse.x, event.mouse.y);
					for(auto &widget : widgets)
					{
						if(widget->checkHit(mouse))
						{
							hitUI = true;
							break;
						}
					}
					if(hitUI)
					{
						continue;
					}

					if(placingCross)
					{
						Coordinates newCoords = Renderer::TransformToGameCoordinates(Coordinates(event.mouse.x, event.mouse.y));
						if(validPoints.count(newCoords) == 0)
						{
							validPoints.insert(newCoords);
							startPoints.insert(newCoords);
							placingCross = false;
							extraPoints -= 1;
							crossPlaceButton->text = std::string("Place cross ") + std::to_string(extraPoints);
							if(extraPoints == 0)
							{
								widgets.erase(std::find(widgets.begin(), widgets.end(), crossPlaceButton));
								delete crossPlaceButton;
								crossPlaceButton = nullptr;
							}
						}
					}
					else if(!makingLine)
					{
						makingLine = true;
						tempPoint = Renderer::TransformToGameCoordinates(Coordinates(event.mouse.x, event.mouse.y));
					}
					else
					{
						makingLine = false;
						Line newLine(tempPoint, Renderer::TransformToGameCoordinates(Coordinates(event.mouse.x, event.mouse.y)));
						if(!newLine.valid)
						{
							continue;
						}
						if(lines.size() > 49)
						{
							newLine.color = al_map_rgba(0, 102, 0, 255);
						}
						if(lines.size() > 99)
						{
							newLine.color = Renderer::red;
						}
						if(lines.size() > 149)
						{
							newLine.color = al_map_rgba(191, 95, 0, 255);
						}
						if(lines.size() > 199)
						{
							newLine.color = Renderer::purple;
						}
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
							continue;
						}

						bool valid = true;
						for(auto &line : lines)
						{
							if(line.checkOverlapping(newLine))
							{
								valid = false;
								break;
							}
						}
						if(!valid)
						{
							continue;
						}

						if(existingPoints == 5)
						{
							extraPoints += 1;
							if(extraPoints == 1)
							{
								crossPlaceButton = new Button(Coordinates(0, 25), Coordinates(100, 25), &Renderer::white, &Renderer::blue, std::string("Place cross ") + std::to_string(extraPoints), placeCross);
								widgets.push_back(crossPlaceButton);
							}
							crossPlaceButton->text = std::string("Place cross ") + std::to_string(extraPoints);
						}
						lines.push_back(newLine);
						for(auto point : newLine.coordinates)
						{
							validPoints.insert(point);
						}
						checkForPossibleMoves();
					}
				}
				else
				{
					makingLine = false;
					placingCross = false;
				}
			}
			else if(event.type == ALLEGRO_EVENT_DISPLAY_RESIZE)
			{
				al_acknowledge_resize(event.display.source);
			}
		}
		al_clear_to_color(Renderer::white);
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

		if(placingCross)
		{
			ALLEGRO_MOUSE_STATE mouse;
			al_get_mouse_state(&mouse);
			Renderer::drawCross(Renderer::TransformToGameCoordinates(Coordinates(mouse.x, mouse.y)), &Renderer::blue);
		}

		for(auto &widget : widgets)
		{
			widget->draw();
		}

		Renderer::drawText(Coordinates(5, 5), &Renderer::black, std::to_string(lines.size()));

		// Finish render
		al_hold_bitmap_drawing(false);

		// Draw the rendering
		al_flip_display();
	}
	for(auto &widget : widgets)
	{
		delete widget;
	}
	widgets.clear();
	validPoints.clear();
	startPoints.clear();
	lines.clear();
	return stayOpen;
}
