#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "allegro5/allegro.h"
#include "Primitives.h"

class GameObject
{
    protected:
        Point position;
        bool is_point_in_rectangle(BoundingBox r, Point p);

    public:
        int speed;
        Vector heading;
        virtual void setPosition(double _x, double _y) = 0;
        virtual void move() = 0;
        Point getPosition();
        void setX(double _x);
        void setY(double _y);
        double getX();
        double getY();
        bool checkCollision(GameObject* gameObject);
        BoundingBox boundingBox;
        ALLEGRO_COLOR color;
        // GameObject(Point position, Vector heading, int speed, ALLEGRO_COLOR color);
};

#endif