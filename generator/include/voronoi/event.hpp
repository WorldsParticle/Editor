#ifndef EVENT_H
#define EVENT_H

#include "../map/point.hpp"
#include "../map/zone.hpp"

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

    explicit Event(Point *p, bool ispe) :
        arch(NULL),
        point(p),
        is_par_event(ispe),
        y(p->y) {}

    Parabola    *arch; // if interesection
    Point       *point; // if point
    bool        is_par_event;
    double      y;

    // Doit y'avoir moyen rester sur une map ou un set simple, voir une liste
    struct compareEvent : public std::binary_function<Event *, Event *, bool>
    {
        bool    operator()(const Event *l, const Event *r) const
        { return (l->y < r->y); }
    };

};

}

#endif // EVENT_H
