#ifndef EVENT_H
#define EVENT_H

#include "../map/point.h"
#include "../map/zone.h"

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

    explicit Event(MAP::Zone *p) :
        type(POINT),
        intersect(0, 0),
        arch(NULL),
        site(p),
        y(p->point.y) {}

    explicit Event(Parabola *a, const Point &p) :
        type(INTERSECTION),
        intersect(p.x, p.y),
        arch(a),
        site(NULL),
        y(p.y) {}

    Type        type;

    Point       intersect; // if intersection
    Parabola    *arch; // if interesection
    MAP::Zone   *site; // if point
    double      y;

    // Doit y'avoir moyen rester sur une map ou un set simple, voir une liste
    struct compareEvent : public std::binary_function<Event *, Event *, bool>
    {
        bool    operator()(const Event *l, const Event *r) const
        {
            if (l->y == r->y) // A refaire
            {
                double xl, xr;
                if (l->type == POINT)
                    xl = l->site->point.x;
                else
                    xl = l->intersect.x;
                if (r->type == POINT)
                    xr = l->site->point.x;
                else
                    xr = l->intersect.x;
                return (xl > xr);
            }
            else
            return (l->y < r->y);
        }
    };

};

}

#endif // EVENT_H
