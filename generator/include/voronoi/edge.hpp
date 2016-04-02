#ifndef EDGE_H
#define EDGE_H

#include "../map/point.hpp"
#include "../map/zone.hpp"

namespace VOR
{

/*
    A class that stores an edge in Voronoi diagram

    start		: pointer to start point
    end			: pointer to end point
    left		: pointer to Voronoi place on the left side of edge
    right		: pointer to Voronoi place on the right side of edge

    neighbour	: some edges consist of two parts, so we add the pointer to another part to connect them at the end of an algorithm

    direction	: directional vector, from "start", points to "end", normal of |left, right|
    f, g		: directional coeffitients satisfying equation y = f*x + g (edge lies on this line)
*/
class Edge  // should find a way to not use it
{
public:

    Point       *start;
    Point       *end;
    Point       *direction;
    Point       *left;
    Point       *right;

    double		f;
    double		g;

    Edge * neighbour;

    /*
        Constructor of the class

        s		: pointer to start
        l		: pointer to left place
        r		: pointer to right place
    */

    Edge(Point *s, Point *l, Point *r) :
        start(s),
        end(NULL),
        direction(NULL),
        left(l),
        right(r)
    {
        neighbour	= NULL;

        f = (r->x - l->x) / (l->y - r->y) ;
        g = s->y - f * s->x ;

        // Revoir
        direction = new Point((r->y - l->y),
                              -(r->x - l->x));
    }

    inline friend std::ostream &operator<<(std::ostream &os, const Edge &e)
    { return os << "[" << *e.left << "|" << *e.right << "]s" << *e.start << "d" << *e.direction; }
};

}

#endif // EDGE_H
