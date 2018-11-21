#include "headers/Word.h"

Word::Word(string _data, double _x, double _y, double _speed, ALLEGRO_COLOR _color) {
    data = _data;
    speed = _speed;
    setPosition(_x, _y);
    size = _data.size() * 15; // ????
    color = _color;
}

void Word::setPosition(double _x, double _y){
    position.x = _x;
    position.y = _y;

    boundingBox.x1 = _x - size/2;
    boundingBox.x2 = _x + size/2;
    boundingBox.y1 = _y;
    boundingBox.y2 = _y + letter_size;

    heading.direction.y = 1;
    heading.direction.x = 0; 
}

void Word::move() {
    setPosition(position.x + (heading.direction.x)*speed,
        position.y + (heading.direction.y)*speed);
}