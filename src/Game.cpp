#include "headers/Word.h"
#include "headers/Words.h"
#include "headers/Game.h"
#include "headers/Menu.h"
#include "headers/Projectile.h"
#include "headers/Projectiles.h"
#include "headers/GameObject.h"
#include "headers/Scores.h"
#include <iostream>

#define VERTICAL 10
#define HORIZONTAL -10

Game::Game(ALLEGRO_DISPLAY* d, ALLEGRO_EVENT_QUEUE* q, Menu* m) {
	display = d;
	queue = q;
	screen_height = al_get_display_height(d);
	screen_width = al_get_display_width(d);
	playerAreaHeight = screen_height / 12;

	/*	GAME ELEMENTS	*/
	init();
	
	wordFont = al_load_ttf_font("fonts/ll_pixel.ttf", 20, 0);
	inputFont = al_load_ttf_font("fonts/hemi_head.ttf", 20, 0);

	inGameMenu = m;
	m->initMenu(this);
}

void Game::init() {
	/*	GAME ELEMENTS	*/
	scores = new Scores();
	words_helper = new Words("src/words.txt", screen_height, screen_width, scores);
	projectiles = new Projectiles(words_helper);
}

Game::~Game() {
	renderStop.store(true);
}

void Game::set_difficulty(int diff){
	// TODO: throw error or smt.
	if (diff > 0) {
		difficulty = diff;
	} else {
		difficulty = 1;
	}
}

void Game::togglePause() {
	renderStop.store(true);
	if(!inGameMenu->menu_running) {
		inGameMenu->options = {"Resume", "Quit"};
		inGameMenu->initMenu(this);
	}else {
		inGameMenu->menu_running = false;
	}
	renderStop.store(false);
}

void Game::moveWords(int moveBy, int axis) {
	switch (axis)
	{
		case HORIZONTAL:
			for(Word* w : words_helper->getWordsOnScreen()) {
				// write the word to the given position
				w->setX(w->getX() + moveBy);
				// anchor the word to the leftmost of screen
				if ((w->getX() + w->size) >= screen_width) {
					w->setX(screen_width - w->size);
				}else if (w->getX() <= 0) {
					w->setX(0);
				}
			}
			break;
	
		case VERTICAL:
			for(Word* w : words_helper->getWordsOnScreen()) {
				// write the word to the given position
				w->setY(w->getY()+moveBy);
			}
			break;
	}
}

void Game::handleInput(ALLEGRO_EVENT event){
	string currentStr (words_helper->getInputWord());

	switch (event.keyboard.keycode)
	{
		case ALLEGRO_KEY_RIGHT:
			moveWords(50, HORIZONTAL);
			break;
		case ALLEGRO_KEY_LEFT:
			moveWords(-50, HORIZONTAL);
			break;
		case ALLEGRO_KEY_UP:
			moveWords(-50, VERTICAL);
			break;
		case ALLEGRO_KEY_DOWN:
			moveWords(50, VERTICAL);
			break;
		case ALLEGRO_KEY_ENTER:
		case ALLEGRO_KEY_SPACE:
		{
			if (!currentStr.empty()) {
				// check if the types words is on screen
				Word* foundWord = words_helper->isIn(currentStr);
				
				currentStr = "";

				if (foundWord == NULL) {
					this -> moveWords(30*difficulty, VERTICAL);
				}else {
					projectiles->clearProjectiles();
					words_helper->eraseWord(foundWord);
				}
			}
			break;
		}
		case ALLEGRO_KEY_ESCAPE:
			togglePause();
			break;
		case ALLEGRO_KEY_BACKSPACE:
			if(!currentStr.empty()){
				currentStr = currentStr.substr(0, currentStr.size()-1);
				
				// check which words contain the input string 
				vector<Word*> targetWords = words_helper->lettersAreIn(currentStr);
				if (targetWords.empty())
					inputColor = al_map_rgb(255, 0, 0);
				else
					inputColor = al_map_rgb(255, 255, 255);
			}
			break;
		default: /* Character inputs */
			{
				char key[5] = {0,0,0,0,0};
				al_utf8_encode(key, event.keyboard.unichar <= 32 ? ' ' : event.keyboard.unichar);
				currentStr += key;

				// Color the input text
				vector<Word*> targetWords = words_helper->lettersAreIn(currentStr);
				
				for (Word* targetWord : targetWords) {
					if (targetWord->getY() < 0){
						inputColor = al_map_rgb(255, 0, 0);
					}
					else {
						inputColor = al_map_rgb(255, 255, 255);
						Projectile* p = new Projectile(screen_width/2, screen_height-playerAreaHeight, 5, 8,
								targetWord, targetWord->color);
						// Launch projectile
						projectiles->spawnProjectile(p);
					}
				}

				break;
			}
	}
	words_helper->setInputWord(currentStr);
}

void Game::update() {
	if (frameCount % 3 == 0) {
		words_helper->updateWords();
	}
	projectiles->updateProjectiles();
	scores->updatePoints();
}

void Game::start() {
	init();
	// Init the words
	words_helper->spawnRandomWords(15, 3, 2);

	// Render everything
	while(!renderStop.load()) {
		ALLEGRO_EVENT event;
        al_wait_for_event(queue, &event);
        if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
            break;
		if (event.type == ALLEGRO_EVENT_TIMER)
			redraw = true;

		if (event.type == ALLEGRO_EVENT_KEY_CHAR)
			handleInput(event);

		/* Handle resize */
		if (event.type == ALLEGRO_EVENT_DISPLAY_RESIZE) {
            // resize buttons
            al_acknowledge_resize(display);
            screen_width = al_get_display_width(display);
            screen_height = al_get_display_height(display);
            redraw = true;
        }
		if (redraw && al_is_event_queue_empty(queue)) {
            redraw = false;
            al_clear_to_color(al_map_rgb(0, 50, 100));
			if (frameCount < 60)
				frameCount++;
			else 
				frameCount = 0;
			/* Update game elements */
			update();
			
			/* Draw Projectiles */
			for (Projectile* p : projectiles->getProjectiles()) {
				al_draw_filled_circle(p->getX(), p->getY(), p->size, p->color);
			}

			lock.lock();
			/* Draw words */
			for(Word* w : words_helper->getWordsOnScreen())
			{
				al_draw_text(wordFont, w->color, w->getX(), w->getY(),
					ALLEGRO_ALIGN_CENTER, w->data.c_str());
				// bounding box of word
				al_draw_rectangle(w->boundingBox.x1, w->boundingBox.y1, w->boundingBox.x2, w->boundingBox.y2, w->color, 3);

				// normals
				// Point middle = Point(screen_width/2, screen_width/2);
				// al_draw_filled_circle(middle.getX(), middle.getY(), 5, al_map_rgb(255,255,255));
				// for (Line line : w->boundingBox.getLines()) {
				// 	Point lineMid = line.getMiddle();
				// 	al_draw_line(lineMid.getX(), lineMid.getY(),
				// 		lineMid.getX()+line.getNormal(middle).direction.getX()*20,
				// 		lineMid.getY()+line.getNormal(middle).direction.getY()*20, al_map_rgb(255,255,255), 2);
				// }
			}
			lock.unlock();

			for (Score* s : scores->scores_on_screen){
				al_draw_text(wordFont, al_map_rgb(255,255,255), s->position.getX(),
				 s->position.getY(), ALLEGRO_ALIGN_CENTER, ("+" + std::to_string(s->getScore())).c_str());
			}

			/* Draw user area */
			al_draw_filled_rectangle(0, screen_height-playerAreaHeight, screen_width, screen_height, al_map_rgb(0,0,0));
			// draw input
			al_draw_text(inputFont, inputColor, 
				screen_width/24, screen_height-playerAreaHeight+10, ALLEGRO_ALIGN_LEFT, words_helper->getInputWord().c_str());
            
			// Score
			al_draw_text(inputFont, al_map_rgb(255,255,255), screen_width-screen_width/24, screen_height-playerAreaHeight+10, 
				ALLEGRO_ALIGN_CENTER, std::to_string(scores->getTotalScore()).c_str());

			al_flip_display();
        }

		// Player stats
		// TODO: Health bar, points, difficulty, level(?)
	}
}
