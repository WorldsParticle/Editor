#ifndef POINT_H
#define POINT_H

#include <iostream>

class   Point
{
public:
    explicit Point(double nx = 0, double ny = 0) : x(nx), y(ny) {}

    Point(const Point &p) : x(p.x), y(p.y) {}

    inline Point &operator=(const Point &p)
    { x = p.x; y = p.y; return *this; }

    inline friend std::ostream &operator<<(std::ostream &os, const Point &p)
    { return os << "(" << p.x << ", " << p.y << ")"; }

    inline bool operator==(const Point &other)
    { return (x == other.x) && (y == other.y); }

    inline bool operator!=(const Point &other)
    { return !(*this == other); }

    double  x;
    double  y;
};

#endif // POINT_H
