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

class Scores;
class Word;
class Words
{
    public:
        Words(string file, int h, int w, Scores* _scores); // constructor 
        ~Words(); // deconstructor
        void spawnRandomWords(int count, int maxSpeed, int speedVarience); /* To get the words which will be seen on the screen */
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
        int screen_height,screen_width;
        int difficulty = 1;

    private:
        vector<Word*> words_on_screen; /* Private to keep stuff thread safe */
        vector<string> all_words;
        vector<Word*> erase_words;
        thread updateWordsTask;
        string inputWord = "";
        Scores* scores;
        mutex mtx; 
};

#endif