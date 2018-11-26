#ifndef PRIMITIVES_H
#define PRIMITIVES_H

struct Point
{
    double x;
    double y;
};

struct BoundingBox
{
    double x1;
    double y1;
    double x2;
    double y2;
};

struct Vector
{
    Point origin;
    Point direction;
};

#endif