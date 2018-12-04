#ifndef GAME_H
#define GAME_H

#include "allegro5/allegro.h"
#include "allegro5/allegro_font.h" /* Text */
#include "allegro5/allegro_ttf.h" /* Text */
#include <bits/stdc++.h> 

using std::string;
using std::vector;
using std::atomic;
using std::thread;

class Scores;
class Word;
class Words;
class Menu;
class Projectiles;
class Game 
{
    public:
        Game(ALLEGRO_DISPLAY* d, ALLEGRO_EVENT_QUEUE* q);
        Game(ALLEGRO_DISPLAY* d, ALLEGRO_EVENT_QUEUE* q, Menu* m);
        Words* words_helper;
		Menu* inGameMenu;
		void set_difficulty(int dif);
		void togglePause();
		void start();
		void update();
		void init();
        ~Game();
        std::atomic<bool> renderStop {false};

    private:
	    ALLEGRO_EVENT_QUEUE* queue;
    	ALLEGRO_DISPLAY* display;
		ALLEGRO_FONT* wordFont;
		ALLEGRO_FONT* inputFont;
		ALLEGRO_COLOR inputColor = al_map_rgb(255,255,255);
		bool redraw;
		int playerAreaHeight;
		int screen_width, screen_height;
		int difficulty = 1;
		void moveWords(int moveBy, int axis);
		void handleInput(ALLEGRO_EVENT event);
		std::mutex lock;
		Projectiles* projectiles;
		Scores* scores; 
		int frameCount = 0;
};

#endif