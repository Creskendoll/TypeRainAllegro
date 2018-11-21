#include "headers/GameObject.h"

bool GameObject::checkCollision(GameObject* gameObject) {
    Point pb1;
    pb1.x = boundingBox.x1; pb1.y = boundingBox.y1;
    Point pb2;
    pb2.x = boundingBox.x2; pb2.y = boundingBox.y1;
    Point pb3;
    pb3.x = boundingBox.x1; pb3.y = boundingBox.y2;
    Point pb4;
    pb4.x = boundingBox.x2; pb4.y = boundingBox.y2;
    
    Point pa1;
    pa1.x = gameObject->boundingBox.x1; pa1.y = gameObject->boundingBox.y1;
    Point pa2;
    pa2.x = gameObject->boundingBox.x2; pa2.y = gameObject->boundingBox.y1;
    Point pa3;
    pa3.x = gameObject->boundingBox.x1; pa3.y = gameObject->boundingBox.y2;
    Point pa4;
    pa4.x = gameObject->boundingBox.x2; pa4.y = gameObject->boundingBox.y2;

    if ( is_point_in_rectangle(boundingBox, pa1) ||
        is_point_in_rectangle(boundingBox, pa2) ||
        is_point_in_rectangle(boundingBox, pa3) ||
        is_point_in_rectangle(boundingBox, pa4))
        return true;
    if ( is_point_in_rectangle(gameObject->boundingBox, pb1) ||
        is_point_in_rectangle(gameObject->boundingBox, pb2) ||
        is_point_in_rectangle(gameObject->boundingBox, pb3) ||
        is_point_in_rectangle(gameObject->boundingBox, pb4))
        return true;
    return false;
}

Point GameObject::getPosition() {
    return position;
}
void GameObject::setX(double _x) {
    setPosition(_x, position.y);
}
void GameObject::setY(double _y){
    setPosition(position.x, _y);
}
double GameObject::getX() {
    return position.x;
}
double GameObject::getY() {
    return position.y;
}