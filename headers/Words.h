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
        void addWord(Word* word);
        void updateWords(unsigned int update_time);
        void removeNLetters(Word* word, int count);
        std::atomic<bool> updateStop {false};
        Word* isIn(string s);
        vector<Word*> lettersAreIn(string s);
        vector<Word*> getWordsOnScreen();
        string getInputWord();
        void setInputWord(string s);

    private:
        vector<Word*> words_on_screen;
        int screen_height,screen_width;
        vector<string> all_words;
        vector<Word*> erase_words;
        thread updateWordsTask;
        string inputWord = "";
        mutex mtx; 
};

#endif