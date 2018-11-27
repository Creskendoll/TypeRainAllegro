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
        };
};

class Vector {
    public:
        Point* origin;
        Point* direction;
        Vector(Point* o, Point* d) {
            origin = o;
            direction = d;
        }
};

class BoundingBox {
    public:
        double x1;
        double y1;
        double x2;
        double y2;
        BoundingBox(double _x1, double _y1, double _x2, double _y2) {
            x1 = _x1; x2 = _x2;
            y1 = _y1; y2 = _y2;
        }
};
