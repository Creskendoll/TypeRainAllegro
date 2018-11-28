#include "headers/GameObject.h"

bool GameObject::is_point_in_rectangle(BoundingBox b_box, Point p) {
    return  (b_box.x1 <= p.getX() && b_box.x2 >= p.getX()) 
                                    &&
            (b_box.y1 <= p.getY() && b_box.y2 >= p.getY());
}

bool GameObject::checkCollision(GameObject* gameObject) {
    Point pa1 = Point(gameObject->boundingBox.x1, gameObject->boundingBox.y1);
    Point pa2 = Point(gameObject->boundingBox.x2, gameObject->boundingBox.y1);
    Point pa3 = Point(gameObject->boundingBox.x1, gameObject->boundingBox.y2);
    Point pa4 = Point(gameObject->boundingBox.x2, gameObject->boundingBox.y2);
    
    Point pb1 = Point(boundingBox.x1, boundingBox.y1);
    Point pb2 = Point(boundingBox.x2, boundingBox.y1);
    Point pb3 = Point(boundingBox.x1, boundingBox.y2);
    Point pb4 = Point(boundingBox.x2, boundingBox.y2);
    
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
    setPosition(_x, position.getY());
}
void GameObject::setY(double _y){
    setPosition(position.getX(), _y);
}
double GameObject::getX() {
    return position.getX();
}
double GameObject::getY() {
    return position.getY();
}