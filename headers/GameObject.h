#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "allegro5/allegro.h"
#include "Primitives.h"

class GameObject
{
    protected:
        Point position;
        Vector heading;

    public:
        int speed;
        bool is_point_in_rectangle(BoundingBox r, Point p) {
            return  (r.x1 <= p.x && r.x2 >= p.x) 
                                &&
                    (r.y1 <= p.y && r.y2 >= p.y);
        }
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