#ifndef WORDS_H
#define WORDS_H

#include <string>
#include <vector>
#include <tuple>
#include <iomanip>
#include <fstream>
#include <bits/stdc++.h>

using std::string;
using std::vector;
using std::tuple;
using std::mutex;
using std::thread;

struct BoundingBox;
class Word;
class Words
{
    public:
        Words(string file, int h, int w); // constructor 
        ~Words(); // deconstructor
        void spawnRandomWords(int count); /* To get the words which will be seen on the screen */
        void eraseWord(Word* word);
        void updateWords(unsigned int update_time);
        std::atomic<bool> updateStop {false};
        Word* isIn(string s);
        Word* lettersAreIn(string s);
        vector<Word*> words_on_screen;

    private:
        int screen_height,screen_width;
        vector<string> all_words;
        vector<Word*> erase_words;
        thread updateWordsTask;
        mutex mtx; 
};

#endif