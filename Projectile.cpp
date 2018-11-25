#include "headers/Projectile.h"
#include "headers/Word.h"

#include <math.h>

Projectile::Projectile(double _x, double _y, int _size, int _speed, Word* _targetWord, ALLEGRO_COLOR _color) {
    setPosition(_x, _y);
    size = _size;
    speed = _speed;
    color = _color;
    targetWord = _targetWord;

    heading.origin = position;
    double distX = targetWord->getX() - _x;
    double distY = targetWord->getY() - _y;
    distance_to_target = sqrt(distX*distX + distY*distY);
    heading.direction.x = distX / distance_to_target;  
    heading.direction.y = distY / distance_to_target;
}
void Projectile::setPosition(double _x, double _y) {
    position.x = _x;
    position.y = _y;

    boundingBox.x1 = position.x - size;
    boundingBox.y1 = position.y - size;
    boundingBox.x2 = position.x + size;
    boundingBox.y2 = position.y + size;
}

void Projectile::move(){
    setPosition(position.x + heading.direction.x*speed,
        position.y + heading.direction.y*speed);
}

Projectile::~Projectile(){
    
}