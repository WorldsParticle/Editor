#ifndef EVENT_H
#define EVENT_H

#include "../map/point.h"

namespace VOR

{

class Parabola;

///
/// \brief The QueuedEvent class
/// represent an event (next point in x coordinate or intersection of three circles)
/// \todo Replace with Site when sure of implementation
///
class Event
{

public:

    enum Type
    {
        POINT = 0,      // Site, add parabola
        INTERSECTION    // Vertex, remove parabola
    };

    explicit Event(const Point &p, Type t) : type(t), arch(NULL), point(p.x, p.y), y(p.y) {}

    Type        type;

    Parabola    *arch; // if interesection
    Point       point; // if point
    double      y;

    // Doit y'avoir moyen rester sur une map ou un set simple, voir une liste
    struct compareEvent : public std::binary_function<Event *, Event *, bool>
    {
        bool    operator()(const Event *l, const Event *r) const { return (l->y > r->y); }
    };

};

}

#endif // EVENT_H
