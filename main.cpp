#include <stdio.h>
#include "headers/Menu.h"
#include "headers/Game.h"

const float FPS = 60;

int main(void) {
    /* Our window. */
    ALLEGRO_DISPLAY *display = NULL;
    /* Event queue */
    ALLEGRO_EVENT_QUEUE* queue = NULL;
    ALLEGRO_TIMER *timer = NULL;

    std::vector<std::string> mainMenuOptions = {"Easy", "Hard", "Multiplayer", "Quit"};

    srand(time(NULL));

    /* Init Allegro 5 + addons. */
	// Initialize allegro
	if (!al_init()) {
		fprintf(stderr, "Failed to initialize allegro.\n");
		return 1;
	}
    al_install_mouse();
    al_install_keyboard();
    al_init_primitives_addon();
    al_init_font_addon();
    al_init_ttf_addon();

    // Initialize the timer
	timer = al_create_timer(1.0 / FPS);
	if (!timer) {
		fprintf(stderr, "Failed to create timer.\n");
		return 1;
	}

    /* Create our window. */
    al_set_new_display_flags(ALLEGRO_RESIZABLE);
    display = al_create_display(720, 720);
    if (!display) {
		fprintf(stderr, "Failed to create display.\n");
        return 1;
	}
    al_set_window_title(display, "Type Rain");

	// Create the event queue
	queue = al_create_event_queue();
	if (!queue) {
		fprintf(stderr, "Failed to create event queue.");
		return 1;
	}

    /* Register events */
    al_register_event_source(queue, al_get_keyboard_event_source());
    al_register_event_source(queue, al_get_display_event_source(display));
    al_register_event_source(queue, al_get_timer_event_source(timer));

	// Start the timer
	al_start_timer(timer);

    /* Run the game */
    Menu* menu = new Menu(display, queue, mainMenuOptions);
    menu -> initMenu(NULL);
}