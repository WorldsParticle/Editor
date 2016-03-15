#ifndef POINT_H
#define POINT_H

#include <iostream>

class   Point
{
public:
    explicit Point(double nx, double ny) : x(nx), y(ny) {}

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
