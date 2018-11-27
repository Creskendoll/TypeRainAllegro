#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "allegro5/allegro.h"
#include "Primitives.cpp"

class BoundingBox;
class Vector;
class Point;
class GameObject
{
    protected:
        virtual void setBoundingBox(double _x, double _y) = 0;
        Point* position = new Point(0,0);
        bool is_point_in_rectangle(BoundingBox* r, Point* p);

    public:
        double speed;
        Vector* heading;
        virtual void setPosition(double _x, double _y) = 0;
        virtual void move() = 0;
        Point* getPosition();
        void setX(double _x);
        void setY(double _y);
        double getX();
        double getY();
        bool checkCollision(GameObject* gameObject);
        BoundingBox* boundingBox;
        ALLEGRO_COLOR color;
        // GameObject(Point position, Vector heading, int speed, ALLEGRO_COLOR color);
};

#endif