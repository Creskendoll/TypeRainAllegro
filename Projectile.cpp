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
    double distY = _y - targetWord->getY();
    distance_to_target = sqrt(distX*distX + distY*distY);
    heading.direction.x = distX;  
    heading.direction.y = distY;
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
    double distX = targetWord->getX() - position.x;
    double distY = targetWord->getY() - position.y;
    distance_to_target = sqrt(distX*distX + distY*distY);
    
    heading.direction.x = distX;  
    heading.direction.y = distY;

    setPosition(position.x + (heading.direction.x/distance_to_target)*speed,
        position.y + (heading.direction.y/distance_to_target)*speed);
}

Projectile::~Projectile(){
    
}