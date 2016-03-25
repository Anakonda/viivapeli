#include "main.h"

std::vector<Widget*> menuWidgets;

bool running = true;

void destroyWidget(Widget* widget)
{
	menuWidgets.erase(std::find(menuWidgets.begin(), menuWidgets.end(), widget));
	delete widget;
}

void startGame(Widget*)
{
	Game game;
	running = game.mainloop();
}

void quit(Widget*)
{
	running = false;
}


int main(int argc, char **argv)
{
	al_init();
	al_install_mouse();

	Renderer::init();

	eventQueue = al_create_event_queue();

	al_register_event_source(eventQueue, al_get_display_event_source(Renderer::getDisplay()));
	al_register_event_source(eventQueue, al_get_mouse_event_source());

	{
		menuWidgets.push_back(new Button(Coordinates(-50, -10), std::pair<Alignment,Alignment>(Alignment::CENTER, Alignment::CENTER), Coordinates(100, 20), &Renderer::white, &Renderer::black, std::string("New Game"), startGame));
		menuWidgets.push_back(new Button(Coordinates(-100, 1), std::pair<Alignment,Alignment>(Alignment::RIGHT, Alignment::TOP), Coordinates(100, 25), &Renderer::white, &Renderer::red, std::string("Quit"), quit));
	}

	while (running)
	{
		ALLEGRO_EVENT event;
		while(al_get_next_event(eventQueue, &event))
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
					bool hitUI = false;
					Coordinates mouse(event.mouse.x, event.mouse.y);
					for(auto &widget : menuWidgets)
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
				}
			}
			else if(event.type == ALLEGRO_EVENT_DISPLAY_RESIZE)
			{
				al_acknowledge_resize(event.display.source);
				Coordinates newSize = Coordinates(al_get_display_width(Renderer::getDisplay()), al_get_display_height(Renderer::getDisplay()));
				for(auto &widget : menuWidgets)
				{
					widget->resize(newSize);
				}
			}
		}
		al_clear_to_color(Renderer::white);
		// Begin render
		al_hold_bitmap_drawing(true);
		for(auto &widget : menuWidgets)
		{
			widget->draw();
		}
		al_hold_bitmap_drawing(false);

		// Draw the rendering
		al_flip_display();
	}

	al_destroy_event_queue(eventQueue);

	Renderer::deinit();
	return 0;
}

