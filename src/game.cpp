
#include "game.h"

bool gameRunning;

bool stayOpen = true;

ALLEGRO_EVENT_QUEUE *eventQueue;

Game* gamePointer = nullptr;

void placeCross(Widget*)
{
	gamePointer->placingCross = true;
}

void close(Widget*)
{
	stayOpen = true;
	gameRunning = false;
}

void removeWidget(Widget* widget)
{
	gamePointer->widgets.erase(std::find(gamePointer->widgets.begin(), gamePointer->widgets.end(), widget));
	delete widget;
}

void undo(Widget*)
{
	if(gamePointer->moveHistory.size() == 0)
	{
		return;
	}
	Game::Move *moveToUndo = &gamePointer->moveHistory.at(gamePointer->moveHistory.size() - 1);
	if(moveToUndo->type == 1)
	{
		if(moveToUndo->line != gamePointer->lines.at(gamePointer->lines.size() - 1))
		{
			//return;
		}
		Line lineToUndo = moveToUndo->line;
		gamePointer->lines.pop_back();

		gamePointer->validPoints = gamePointer->startPoints;
		for(auto &line : gamePointer->lines)
		{
			for(auto point : line.coordinates)
			{
				gamePointer->validPoints.insert(point);
			}
		}

		bool allPoints = true;
		for(auto &point : lineToUndo.coordinates)
		{
			if(gamePointer->validPoints.find(point) == gamePointer->validPoints.end())
			{
				allPoints = false;
				break;
			}
		}
		if(allPoints)
		{
			gamePointer->extraPoints -= 1;
			if(gamePointer->extraPoints == 0)
			{
				gamePointer->widgets.erase(std::find(gamePointer->widgets.begin(), gamePointer->widgets.end(), gamePointer->crossPlaceButton));
				delete gamePointer->crossPlaceButton;
				gamePointer->crossPlaceButton = nullptr;
			}
		}
	}
	else
	{
		gamePointer->validPoints.erase(moveToUndo->point);
		if(gamePointer->startPoints.find(moveToUndo->point) == gamePointer->startPoints.end())
		{
			std::cout<<moveToUndo->point<<std::endl;
		}
		gamePointer->startPoints.erase(moveToUndo->point);
		gamePointer->extraPoints += 1;
		if(gamePointer->extraPoints == 1)
		{
			gamePointer->crossPlaceButton = new Button(Coordinates(0, 25), std::pair<Alignment,Alignment>(Alignment::LEFT,Alignment::TOP), Coordinates(100, 25), &Renderer::white, &Renderer::blue, std::string("Place cross ") + std::to_string(gamePointer->extraPoints), placeCross);
			gamePointer->widgets.push_back(gamePointer->crossPlaceButton);
		}
		gamePointer->crossPlaceButton->text = std::string("Place cross ") + std::to_string(gamePointer->extraPoints);
	}
	gamePointer->moveHistory.pop_back();
}

void ToggleClues(Widget* button)
{
	gamePointer->showPossibleMoves = !(gamePointer->showPossibleMoves);
	if(gamePointer->showPossibleMoves)
	{
		((Button*)button)->text = std::string("Hide possible moves.");
	}
	else
	{
		((Button*)button)->text = std::string("Show possible moves.");
	}
}

void checkForPossibleMoves()
{
	gamePointer->possibleMoves.clear();
	for(auto &point : gamePointer->validPoints)
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
			for(auto &line : gamePointer->lines)
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
					if(gamePointer->validPoints.count(coordinate) > 0)
					{
						existingPoints++;
					}
				}
				if(existingPoints > 3)
				{
					Line possibleMove;
					possibleMove = tempLine;
					possibleMove.color = Renderer::cyan;
					gamePointer->possibleMoves.push_back(possibleMove);
				}
			}
		}
	}
	if(gamePointer->possibleMoves.empty())
	{
		if(gamePointer->extraPoints == 0)
		{
			gamePointer->widgets.push_back(new Button(Coordinates(-100, -10), std::pair<Alignment,Alignment>(Alignment::CENTER, Alignment::CENTER), Coordinates(200, 20), &Renderer::white, &Renderer::red, std::string("No more valid moves."), removeWidget));
		}
	}
}


Game::Game()
{
	gamePointer = this;
	this->extraPoints = 0;
	this->showPossibleMoves = false;

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
		widgets.push_back(new Button(Coordinates(-100, 0), std::pair<Alignment,Alignment>(Alignment::RIGHT, Alignment::TOP), Coordinates(100, 25), &Renderer::white, &Renderer::red, std::string("Close"), close));
		widgets.push_back(new Button(Coordinates(0, -25), std::pair<Alignment,Alignment>(Alignment::LEFT, Alignment::BOTTOM), Coordinates(150, 25), &Renderer::white, &Renderer::blue, std::string("Show possible moves."), ToggleClues));
		widgets.push_back(new Button(Coordinates(-50, -25), std::pair<Alignment,Alignment>(Alignment::RIGHT, Alignment::BOTTOM), Coordinates(50, 25), &Renderer::white, &Renderer::blue, std::string("Undo"), undo));
	}

	checkForPossibleMoves();
}


bool Game::mainloop()
{
	gameRunning = true;


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
							checkForPossibleMoves();

							Move newMove;
							newMove.point = newCoords;
							newMove.type = 2;
							moveHistory.push_back(newMove);
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
							newLine.color = Renderer::purple;
						}
						if(lines.size() > 199)
						{
							newLine.color = Renderer::black;
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
								crossPlaceButton = new Button(Coordinates(0, 25), std::pair<Alignment,Alignment>(Alignment::LEFT,Alignment::TOP), Coordinates(100, 25), &Renderer::white, &Renderer::blue, std::string("Place cross ") + std::to_string(extraPoints), placeCross);
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

						Move newMove;
						newMove.line = lines.at(lines.size() - 1);
						newMove.type = 1;
						moveHistory.push_back(newMove);
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
				Coordinates newSize = Coordinates(al_get_display_width(Renderer::getDisplay()), al_get_display_height(Renderer::getDisplay()));
				for(auto &widget : this->widgets)
				{
					widget->resize(newSize);
				}
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

		if(showPossibleMoves)
		{
			for(auto &line : possibleMoves)
			{
				Coordinates start = Renderer::TransformToScreenCoordinates(line.start);
				Coordinates end = Renderer::TransformToScreenCoordinates(line.end);
				al_draw_line(start.x, start.y, end.x, end.y, line.color, 2);
			}
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
