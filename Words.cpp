#include "headers/Word.h"
#include "headers/Words.h"
#include "headers/Helper.h"

// Initialize all_words and fill it with all the words in the read file 
Words::Words(string file, int h, int w)
{
    screen_height = h;
    screen_width = w;

    std::ifstream inFile;
    string word_buffer;
    
    inFile.open(file);
    if (!inFile) {
        std::cout << "Unable to open file";
        exit(1); // terminate with error
    }
    
    while (inFile >> word_buffer) {
        this -> all_words.push_back(word_buffer);
    }
    
    inFile.close();

    updateWordsTask = thread(&Words::updateWords, this, 30);
}

// Erase the given word from the vector
void Words::eraseWord(Word* word) {
    mtx.lock();
    words_on_screen.erase(std::remove(words_on_screen.begin(), words_on_screen.end(), word), words_on_screen.end());
    mtx.unlock();
}

void Words::updateWords(unsigned int update_time) {
	while(true) {
		if(!updateStop.load()) {
            for(Word* w : words_on_screen) {
                w->move();
                if (w->getY() >= screen_height) {
                    eraseWord(w);
                    spawnRandomWords(1);
                }
            }
			// wait between updates
			std::this_thread::sleep_for(std::chrono::milliseconds(update_time));
		}
	}
}

// fills words on screen with a set of {count} words
void Words::spawnRandomWords(int count) {
    for(int i = 0; i < count; i++)
    {
        int randomIndex = rand() % this->all_words.size();
        string word = this->all_words.at(randomIndex);
        int word_y, word_x;
        word_y = -(rand() % screen_height) * 2;
        word_x = (rand() % (screen_width-word.size()*20)) + word.size()*10;

        // Random color
        int randR = rand() % 255;
        int randG = rand() % 255;
        int randB = rand() % 255;
        Word* newWord = new Word(word, word_x, word_y, 2, al_map_rgb(randR, randG, randB));

        // check if words are colliding
        bool flag = true;
        while (flag) {
            flag = false;
            for (Word* w : words_on_screen) {
                if (newWord->checkCollision(w)) {
                    flag = true;
                    word_y = -(rand() % screen_height) * 2;
                    word_x = (rand() % (screen_width-word.size()*20)) + word.size()*10;
                    newWord = new Word(word, word_x, word_y, 2, al_map_rgb(randR, randG, randB));
                }
            }
        }
        
        mtx.lock();
        words_on_screen.push_back(newWord);
        mtx.unlock();
    }
}

Word* Words::isIn(string s){
    if (!s.empty()) {
        for (Word* w : words_on_screen) { 
            if (!w->data.compare(s)) {
                return w;
            }
        }
    }
    return NULL;
}

Word* Words::lettersAreIn(string s){
    if (!s.empty()) {
        for (Word* w : words_on_screen) { 
            if (!w->data.substr(0, s.size()).compare(s)) {
                return w;
            }
        }
    }
    return NULL;
}