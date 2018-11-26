#include "headers/Projectile.h"
#include "headers/Word.h"

#include <math.h>

Projectile::Projectile(double _x, double _y, int _size, int _speed, Word* _targetWord, ALLEGRO_COLOR _color) {
    position = new Point(_x, _y);
    setBoundingBox(_x, _y);
    size = _size;
    speed = _speed;
    color = _color;
    targetWord = _targetWord;

    double distX = targetWord->getX() - _x;
    double distY = targetWord->getY() - _y;
    distance_to_target = sqrt(distX*distX + distY*distY);

    heading->origin = position;
    // normalized direction
    heading->direction = new Point(distX / distance_to_target, distY / distance_to_target);
}

void Projectile::setBoundingBox(double _x, double _y) {
    boundingBox->x1 = position->getX() - size;
    boundingBox->y1 = position->getY() - size;
    boundingBox->x2 = position->getX() + size;
    boundingBox->y2 = position->getY() + size;
}

void Projectile::setPosition(double _x, double _y) {
    position->set(_x, _y);
    setBoundingBox(_x, _y);
}

void Projectile::move(){
    setPosition(position->getX() + heading->direction->getX()*speed,
        position->getY() + heading->direction->getY()*speed);
}

Projectile::~Projectile(){
    
}