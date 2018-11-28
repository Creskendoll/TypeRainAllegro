#include <math.h>
#include <vector>

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
        Point(double _x, double _y) { set(_x, _y); }
        Point () { x = 0; y = 0; }
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
            return Point(0,0).distanceTo(direction);
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
            Point dir = Point(direction.getX() - 2*dotProd * normal.direction.getX(),
                                direction.getY() - 2*dotProd * normal.direction.getY());
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
        Vector() { direction = Point(); }
};

class Line {
    public:
        Point a;
        Point b;
        Line() { a=Point(); b=Point(); }
        Line(Point _a, Point _b) { a = _a; b = _b; }
        Point getMiddle(){
            return Point( (a.getX()+b.getX())/2, (a.getY()+b.getY())/2 );
        }
        Vector getNormal(Point p) {
            double dx = b.getX() - a.getX();
            double dy = b.getY() - a.getY();
            Vector result;
            
            double side = (p.getX()-a.getX())*(b.getY()-a.getY())
                            -(p.getY()-a.getY())*(b.getX()-a.getX());

            if (side >= 0)
                result = Vector(Point(dy, -dx));
            else
                result = Vector(Point(-dy, dx));

            return result;
        }
        double distanceToPoint(Point p) {
            double divided = abs( (b.getY()-a.getY())*p.getX() - 
                 (b.getX()-a.getX())*p.getY() +
                  b.getX()*a.getY()-b.getY()*a.getX());
            double divisor = sqrt( (b.getY()-a.getY())*(b.getY()-a.getY()) +
                                    (b.getX()-a.getX())*(b.getX()-a.getX()) );

            return divided / divisor;
        }
};

class BoundingBox {
    private:
        Line a; Line b;
        Line c; Line d;
    public:
        double x1; double y1;
        double x2; double y2;
        BoundingBox() {
            x1 = 0; x2 = 0;
            y1 = 0; y2 = 0;
        }
        BoundingBox(double _x1, double _y1, double _x2, double _y2) {
            x1 = _x1; x2 = _x2;
            y1 = _y1; y2 = _y2;
            a = Line(Point(x1, y1), Point(x2, y1));
            b = Line(Point(x2, y1), Point(x2, y2));
            c = Line(Point(x2, y2), Point(x1, y2));
            d = Line(Point(x1, y2), Point(x1, y1));
        }
        Vector getRelativeNormal(Point p) {
            double minDist = -1;
            double dist;
            Line l;
            for (Line line : getLines()) {
                dist = line.distanceToPoint(p);
                if (minDist < 0) {
                    minDist = dist;
                    l = line;
                } else if (dist < minDist){
                    minDist = dist;   
                    l = line;
                }
            }
            return l.getNormal(p);
        }
        std::vector<Line> getLines() {
            return std::vector<Line> {a,b,c,d};
        }
};
