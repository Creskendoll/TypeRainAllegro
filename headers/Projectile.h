#ifndef PROJECTILE_H
#define PROJECTILE_H
#include "allegro5/allegro.h"
#include "GameObject.h"

class Word;
class Projectile : public GameObject {
    public:
        int size;
        Word* targetWord;
        void setPosition(double _x, double _y);
        void move();
        double distance_to_target;
        ~Projectile();
        Projectile(double _x, double _y, int _size, int _speed, Word* _targetWord, ALLEGRO_COLOR _color);
};

#endif