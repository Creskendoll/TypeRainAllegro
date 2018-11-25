#ifndef PROJECTILE_H
#define PROJECTILE_H
#include "allegro5/allegro.h"
#include "GameObject.h"

#define PROJECTILE_NORMAL 0
#define PROJECTILE_BOUNCE 1
#define PROJECTILE_SUPER  2

class Word;
class Projectile : public GameObject {
    public:
        int size;
        int type = PROJECTILE_BOUNCE;
        Word* targetWord;
        void setPosition(double _x, double _y);
        void move();
        double distance_to_target;
        ~Projectile();
        Projectile(double _x, double _y, int _size, int _speed, Word* _targetWord, ALLEGRO_COLOR _color);
};

#endif