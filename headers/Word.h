#ifndef WORD_H
#define WORD_H
#include <string>
#include "allegro5/allegro.h"
#include "GameObject.h"

using std::string;

class Word : public GameObject
{
    public: 
        string data;
        void setPosition(double _x, double _y);
        int size;
        int point; // TODO: calculated based on size and color 
        void move();
        ~Word();
        Word(string _data, double _x, double _y, double _speed, ALLEGRO_COLOR color);
        bool operator == (const Word& w)
        {
            return (this->data.compare(w.data) == 0);
        }
    private:
        int letter_size = 30; // ???
};

#endif