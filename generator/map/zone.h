#ifndef ZONE_H
#define ZONE_H

#include <vector>
#include "point.h"

namespace MAP
{

class CrossedEdge;
class Corner;

///
/// \brief The Site class
/// Represent the Delaunay triangulation
/// This is the zone as itself, the face of the polygon
///
class Zone
{

public:

    explicit Zone(double x = 0, double y = 0);

    inline friend std::ostream &operator<<(std::ostream &os, const Zone &s)
    { return os << "[" << s.index << "](" << s.point.x << ", " << s.point.y << ")"; }

    static int  indexMax;  // change this
    const int   index;

    Point       point;     // location
    bool        water;     // lake or ocean
    bool        ocean;     // ocean
    bool        coast;     // land polygon touching an ocean
    bool        border;    // at the edge of the map
    float       elevation; // 0.0-1.0
    float       moisture;  // 0.0-1.0

    std::string biome;     // biome type (see article)

    std::vector<Zone *>         neighbors;
    std::vector<CrossedEdge *>  borders;
    std::vector<Corner *>       corners;
};

}

#endif // ZONE_H
