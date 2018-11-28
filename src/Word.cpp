#include "headers/Word.h"

Word::Word(string _data, double _x, double _y, double _speed, ALLEGRO_COLOR _color) {
    position = Point(_x, _y);
    size = _data.size() * 20; // ????
    setBoundingBox(_x, _y);
    data = _data;
    speed = _speed;
    color = _color;

    heading = Vector(Point(0, 1));

    // score
    point = _data.size();
}

void Word::setBoundingBox(double _x, double _y) {
    boundingBox = BoundingBox(_x - size/2.0, _y, _x + size/2.0, _y + bBox_height);
}

void Word::setPosition(double _x, double _y){
    position.set(_x, _y);
    setBoundingBox(_x, _y);
}

void Word::move() {
    setPosition(position.getX() + heading.direction.getX()*speed,
        position.getY() + heading.direction.getY()*speed);
}
