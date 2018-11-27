#include "headers/Projectile.h"
#include "headers/Word.h"

#include <math.h>

Projectile::Projectile(double _x, double _y, double _size, int _speed, Word* _targetWord, ALLEGRO_COLOR _color) {
    position = Point(_x, _y);
    setBoundingBox(_x, _y);
    size = _size;
    speed = _speed;
    color = _color;
    targetWord = _targetWord;

    heading = Vector(position, targetWord->getPosition());
}

void Projectile::setBoundingBox(double _x, double _y) {
    boundingBox = BoundingBox(position.getX()-size, position.getY()-size, position.getX() + size, position.getY() + size);
}

void Projectile::setPosition(double _x, double _y) {
    position.set(_x, _y);
    setBoundingBox(_x, _y);
}

void Projectile::move(){
    setPosition(position.getX() + heading.direction.getX()*speed,
        position.getY() - heading.direction.getY()*speed);
}

Projectile::~Projectile(){
    
}