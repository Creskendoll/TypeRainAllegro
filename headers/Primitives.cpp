#include <math.h>

class Point {
    private:
        double x;
        double y;
    public:
        double getX() { return x; }
        double getY() { return y; }
        void setX(double _x) { x = _x; }
        void setY(double _y) { y = _y; }
        void set(double _x, double _y) { setX(_x); setY(_y); }
        Point(double _x, double _y) {
            setX(_x); setY(_y);
        }
        Point () {
            x = 0;
            y = 0;
        }
        double distanceTo(Point p){
            double distX = x-p.getX();
            double distY = y-p.getY();
            return sqrt(distX*distX + distY*distY);
        }
};

class Vector {
    public:
        Point direction;
        double magnitude () {
            // Origin in 0,0
            return sqrt(direction.getX()*direction.getX() + direction.getY()*direction.getY());
        }
        double magnitude (Point origin) {
            return direction.distanceTo(origin);
        }
        double dotProduct(Vector v) {
            return direction.getX() * v.direction.getX()
                    + direction.getY() * v.direction.getY();
        }
        Vector reflect(Vector normal) {
            double dotProd = dotProduct(normal);
            Point dir = Point(direction.getX()-2*dotProd * normal.direction.getX(),
                                    direction.getY()-2*dotProd * normal.direction.getY());
            return Vector(dir);
        }
        Vector(Point d) {
            // Origin is (0,0)
            direction = d;
            // Normalized direction
            direction = Point(d.getX()/magnitude(), d.getY()/magnitude());
        }
        Vector(Point o, Point d) {
            // Origin is o
            direction = d;
            // Normalized direction
            direction = Point((d.getX()-o.getX())/magnitude(o), (o.getY()-d.getY())/magnitude(o));
        }
        Vector() {
            direction = Point();
        }
};

class BoundingBox {
    public:
        double x1;
        double y1;
        double x2;
        double y2;
        BoundingBox() {
            x1 = 0;
            x2 = 0;
            y1 = 0;
            y2 = 0;
        }
        BoundingBox(double _x1, double _y1, double _x2, double _y2) {
            x1 = _x1; x2 = _x2;
            y1 = _y1; y2 = _y2;
        }
};
