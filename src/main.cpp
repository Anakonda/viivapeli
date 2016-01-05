#include "main.h"



/*
void destroyWidget(Widget* widget)
{
	widgets.erase(std::find(widgets.begin(), widgets.end(), widget));
	delete widget;
}
*/

int main(int argc, char **argv)
{
	al_init();
	al_install_mouse();

	Renderer::init();

	eventQueue = al_create_event_queue();

	al_register_event_source(eventQueue, al_get_display_event_source(Renderer::getDisplay()));
	al_register_event_source(eventQueue, al_get_mouse_event_source());

	game();

	al_destroy_event_queue(eventQueue);

	Renderer::deinit();
	return 0;
}

