#ifndef CROSSEDEDGE_H
#define CROSSEDEDGE_H

#include "point.h"
#include "zone.h"

namespace MAP
{

class Zone;
class Corner;

///
/// \brief The CrossedEdge class
/// represent both edge of Voronoi and Delaunay graph
/// allowing to connect them together
/// it is the cross point you can see between black and white segment in http://www-cs-students.stanford.edu/~amitp/game-programming/polygon-map-generation/voronoi-and-delaunay.png
/// \todo mettre le coeff directeur des deux droites
///
class CrossedEdge
{

public:

    explicit CrossedEdge();

    inline friend std::ostream &operator<<(std::ostream &os, const CrossedEdge &e)
    { return os << "[" << e.index << "](" << e.z0->index << ", " << e.z1->index << ") mid" << e.midpoint; }

    static int  indexMax;  // change this
    const int   index;

    Zone        *z0, *z1;   // Delaunay edge (during computing, é0 will be used as left, z1 as right)
    Corner      *c0, *c1;   // Voronoi edge
    Point       midpoint;  // cross point, halfway between c0 / c1
    int         river;     // Volume of water, not necessary right now
};

}

#endif // CROSSEDEDGE_H
