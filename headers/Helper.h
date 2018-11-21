#ifndef HELPER_H
#define HELPER_H
#include "Primitives.h"

bool is_point_in_rectangle(BoundingBox r, Point p) {
    return  (r.x1 <= p.x && r.x2 >= p.x) 
                         &&
            (r.y1 <= p.y && r.y2 >= p.y);
}

bool do_rectangles_intersect(BoundingBox a, BoundingBox b) {
    Point pb1;
    pb1.x = b.x1; pb1.y = b.y1;
    Point pb2;
    pb2.x = b.x2; pb2.y = b.y1;
    Point pb3;
    pb3.x = b.x1; pb3.y = b.y2;
    Point pb4;
    pb4.x = b.x2; pb4.y = b.y2;
    
    Point pa1;
    pa1.x = a.x1; pa1.y = a.y1;
    Point pa2;
    pa2.x = a.x2; pa2.y = a.y1;
    Point pa3;
    pa3.x = a.x1; pa3.y = a.y2;
    Point pa4;
    pa4.x = a.x2; pa4.y = a.y2;

    if ( is_point_in_rectangle(b, pa1) ||
         is_point_in_rectangle(b, pa2) ||
         is_point_in_rectangle(b, pa3) ||
         is_point_in_rectangle(b, pa4))
        return true;
    if ( is_point_in_rectangle(a, pb1) ||
         is_point_in_rectangle(a, pb2) ||
         is_point_in_rectangle(a, pb3) ||
         is_point_in_rectangle(a, pb4))
        return true;
    return false;
}

#endif