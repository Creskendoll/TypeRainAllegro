#include "headers/Menu.h"
#include "headers/Game.h"

Menu::Menu(ALLEGRO_DISPLAY* _display, ALLEGRO_EVENT_QUEUE* _queue, vector<string> _options) {
    screen_width = al_get_display_width(_display);
    screen_height = al_get_display_height(_display);
    font = al_load_ttf_font("fonts/mexcellent3d.ttf", 50, 0);
    if(!font) {
        printf("Couldn't load font");
        exit(1);
    }
    queue = _queue;
    display = _display;
    options = _options;
}

Menu::~Menu(){
    menu_running = false;
}

void Menu::drawButtons(int selection) {
    int buttonCount = options.size();
    ALLEGRO_COLOR button_color = al_map_rgb(0, 50, 200);

    int grid_H = screen_height / 12;
    int grid_W = screen_width / 12;

    int buttonHeight = grid_H * 3;
    int buttonWidth = grid_W * 8; 

    for(int i = 0; i < buttonCount; i++)
    {
        // TODO: Even out the buttons
        int margin = grid_H/2;

        if (i == selection) {
            al_draw_filled_rectangle(grid_W * 2, (buttonHeight * i) + margin, buttonWidth + (grid_W * 2), buttonHeight * (i+1), button_color);
        } else {
            al_draw_rectangle(grid_W * 2, (buttonHeight * i) + margin, buttonWidth + (grid_W * 2), buttonHeight * (i+1), button_color, 2.0);
        }

        al_draw_text(font, al_map_rgb(255, 255, 255),
            screen_width/2, (buttonHeight * i) + grid_H, ALLEGRO_ALIGN_CENTRE, options.at(i).c_str());
    }
}

void Menu::initMenu(Game* game) {
    menu_running = true;
    int selection = 0;
    int buttonCount = options.size();
    while(true) {
        if (menu_running) {
        ALLEGRO_EVENT event;
        al_wait_for_event(queue, &event);
        if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
            exit(0);

        /* Button Press */
        if (event.type == ALLEGRO_EVENT_KEY_DOWN) {
            if (event.keyboard.keycode == ALLEGRO_KEY_DOWN) {
                if (selection < (buttonCount - 1)) {
                    selection++;
                } else {
                    selection = 0;
                }
            }
            if (event.keyboard.keycode == ALLEGRO_KEY_UP) {
                if (selection > 0) {
                    selection--;
                } else {
                    selection = buttonCount - 1;
                }
            }
            if (event.keyboard.keycode == ALLEGRO_KEY_ENTER){
                makeSelection(selection, game);
            }
            if (event.keyboard.keycode == ALLEGRO_KEY_ESCAPE)
                break;
        }
        if (event.type == ALLEGRO_EVENT_TIMER)
            menu_redraw = true;
        if (event.type == ALLEGRO_EVENT_DISPLAY_RESIZE) {
            // resize buttons
            al_acknowledge_resize(display);
            screen_width = al_get_display_width(display);
            screen_height = al_get_display_height(display);
            menu_redraw = true;
        }
        if (menu_redraw && al_is_event_queue_empty(queue)) {
            menu_redraw = false;
            al_clear_to_color(al_map_rgb(0, 0, 0));
            drawButtons(selection);
            al_flip_display();
        }
        }
    }
}

void Menu::makeSelection(int selection, Game* game) {
    if(game != NULL) {
        switch (selection)
        {
            case 0: /* Resume */
                menu_running = false;
                game->togglePause();
                break;
            case 1: /* Quit */
                game-> renderStop.store(true);
                menu_running = true;
                break;
            default:
                break;
        }
    } else {
        switch (selection)
        {
            case 0: /* EASY */
            {
                menu_running = false;
                game = new Game(display, queue, this);
                game -> set_difficulty(1);
                game -> start();
                game -> ~Game();
                break;
            }
            case 1: /* HARD */
            {
                menu_running = false;
                game = new Game(display, queue, this);
                game -> set_difficulty(2);
                game -> start();
                game -> ~Game();
                break;
            }
            case 2: /* MULTIPLAYER */
                break;
            case 3: /* QUIT */
                menu_running = false;
                al_destroy_display(display);
                break;
            default:
                break;
        }
    }
}
