#ifndef CORNER_H
#define CORNER_H

#include <vector>
#include "point.h"

namespace MAP
{

class Zone;
class CrossedEdge;

///
/// \brief The Corner class (vertex)
/// represent the vertices of zones
/// contains the shape of Voronoi polygons
///
class Corner
{

public:

    explicit Corner();

    inline friend std::ostream &operator<<(std::ostream &os, const Corner &c)
    { return os << "[" << c.index << "]" << c.point; }

    static int  indexMax;  // change this
    const int   index;

    Point   point;     // location
    bool    ocean;     // ocean
    bool    water;     // lake or ocean
    bool    coast;     // touches ocean and land polygons
    bool    border;    // at the edge of the map
    float   elevation; // 0.0-1.0
    float   moisture;  // 0.0-1.0

    std::vector<Zone *>         faces; // touching faces
    std::vector<CrossedEdge *>  edges; // touching edges
    std::vector<Corner *>       adjacent; // adjacent corners

    int     river;     // 0 if no river, or volume of water in river
    Corner  *downslope; // pointer to adjacent corner most downhill
    Corner  *watershed; // pointer to coastal corner, or null
    int     watershedSize;
};

}

#endif // CORNER_H
