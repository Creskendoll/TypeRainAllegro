#include "headers/Word.h"
#include "headers/Words.h"
#include "headers/Scores.h"

// TODO: game modes
// incremental difficulty

// Initialize all_words and fill it with all the words in the read file 
Words::Words(string file, int h, int w, Scores* _scores)
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

    // updateWordsTask = thread(&Words::updateWordsAsync, this, 50);
    scores = _scores;
}

Words::~Words() {
    updateWordsTask.join();
}
// Erase the given word from the vector
void Words::eraseWordAsync(Word* word) {
    mtx.lock();
    words_on_screen.erase(std::remove(words_on_screen.begin(), words_on_screen.end(), word), words_on_screen.end());
    mtx.unlock();
}
void Words::addWordAsync(Word* word) {
    mtx.lock();
    words_on_screen.push_back(word);
    mtx.unlock();
}
void Words::setInputWordAsync(string s) {
    mtx.lock();
    inputWord = s;
    mtx.unlock();
}

string Words::getInputWord() { return inputWord; }
void Words::setInputWord(string s) { inputWord = s; }
// Erase the given word from the vector
void Words::eraseWord(Word* word) {
    words_on_screen.erase(std::remove(words_on_screen.begin(), words_on_screen.end(), word), words_on_screen.end());
}
void Words::addWord(Word* word) {
    words_on_screen.push_back(word);
}


void Words::removeNLetters(Word* w, int count) {
    string newData = w->data.substr(count, w->data.size()-1);
    // If word is empty
    if (newData.empty()) {
        eraseWord(w);
        // display score 
        scores->addScore(new Score(w->point, w->getPosition(), 40));
        spawnRandomWords(1, difficulty, 3);
    }else{
        w->data = newData;
    }
}

vector<Word*> Words::getWordsOnScreen() {
    return words_on_screen;
}

void Words::updateWordsAsync(unsigned int update_time) {
	while(true) {
		if(!updateStop.load()) {
            for(Word* w : words_on_screen) {
                mtx.lock();
                w->move();
                mtx.unlock();
                if (w->getY() >= screen_height) {
                    eraseWordAsync(w);
                    spawnRandomWords(1, difficulty, 3);
                }

                if (inputWord == w->data) {
                    setInputWordAsync("");
                }
            }
			// wait between updates
			std::this_thread::sleep_for(std::chrono::milliseconds(update_time));
		}
	}
}
void Words::updateWords() {
    if(!updateStop.load()) {
        for(Word* w : words_on_screen) {
            w->move();
            if (w->getY() >= screen_height) {
                eraseWord(w);
                spawnRandomWords(1, difficulty, 3);
            }

            if (inputWord == w->data) {
                setInputWord("");
            }
        }
    }
}

// fills words on screen with a set of {count} words
void Words::spawnRandomWords(int count, int maxSpeed, int speedVarience) {
    for(int i = 0; i < count; i++)
    {
        int randomIndex = rand() % all_words.size();
        string word = all_words.at(randomIndex);
        int word_y, word_x;
        word_x = (rand() % (screen_width-word.size()*20)) + word.size()*10;
        word_y = -(rand() % screen_height) * 2;

        // Random color
        int randR = rand() % 255;
        int randG = rand() % 255;
        int randB = rand() % 255;

        int varience = (rand() % speedVarience) + 1;
        int speed = ( (rand() % maxSpeed) + 1 ) * varience;

        Word* newWord = new Word(word, word_x, word_y, speed, al_map_rgb(randR, randG, randB));
        // check if words are colliding
        bool flag = true;
        while (flag) {
            flag = false;
            for (Word* w : words_on_screen) {
                if (newWord->checkCollision(w)) {
                    flag = true;
                    word_y = -(rand() % screen_height) * 2;
                    word_x = (rand() % (screen_width-word.size()*20)) + word.size()*10;
                    newWord = new Word(word, word_x, word_y, speed, al_map_rgb(randR, randG, randB));
                }
            }
        }
        
        addWord(newWord);
    }
}

// Check if entire word exists
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

// check if s exists as sub string
vector<Word*> Words::lettersAreIn(string s){
    vector<Word*> result;
    if (!s.empty()) {
        for (Word* w : words_on_screen) { 
            if (!w->data.substr(0, s.size()).compare(s)) {
                result.push_back(w);
            }
        }
    }
    return result;
}
