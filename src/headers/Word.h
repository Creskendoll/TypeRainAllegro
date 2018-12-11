#ifndef WORD_H
#define WORD_H
#include <string>
#include "allegro5/allegro.h"
#include "allegro5/allegro_image.h"
#include "GameObject.h"

using std::string;

class Word : public GameObject
{
    public: 
        string data;
        void setPosition(double _x, double _y);
        double size;
        int point; // TODO: calculated based on color 
        ALLEGRO_BITMAP* image = NULL;
        void move();
        ~Word();
        Word(string _data, double _x, double _y, double _speed, ALLEGRO_COLOR color);
        bool operator == (const Word& w)
        {
            return (this->data.compare(w.data) == 0);
        }
    private:
        void setBoundingBox(double _x, double _y);
        int bBox_height = 30; // ???
};

#endif