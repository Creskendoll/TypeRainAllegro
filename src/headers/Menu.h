#ifndef MENU_H
#define MENU_H

#include "allegro5/allegro.h"
#include "allegro5/allegro_primitives.h" /* Rectangles */ 
#include "allegro5/allegro_font.h" /* Text */
#include <bits/stdc++.h> 

using std::vector;
using std::string;
    
class Game;
class Menu
{
private:
    ALLEGRO_FONT* font;
    Game* game;
    bool menu_redraw = true;
    int screen_width, screen_height;
    void drawButtons(int selection);
    void makeSelection(int selection, Game* Game);
    int mouseOverButton(int mouse_x, int mouse_y);
public:
    ALLEGRO_EVENT_QUEUE* queue;
    ALLEGRO_DISPLAY* display;
    vector<string> options;
    bool menu_running = false;
    Menu(ALLEGRO_DISPLAY *display, ALLEGRO_EVENT_QUEUE* _queue, vector<string> _options);
    void initMenu(Game* game);
    ~Menu();
};

#endif
