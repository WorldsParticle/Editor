#ifndef ZONE_H
#define ZONE_H

#include <vector>
#include "point.hpp"

namespace MAP
{

class CrossedEdge;
class Corner;

enum Biome {
    OCEAN,
    MARSH,
    ICE,
    LAKE,
    BEACH,
    SNOW,
    TUNDRA,
    BARE,
    SCORCHED,
    TAIGA,
    SHRUBLAND,
    TEMPERATE_DESERT,
    TEMPERATE_RAIN_FOREST,
    TEMPERATE_DECIDUOUS_FOREST,
    GRASSLAND,
    TROPICAL_SEASONAL_FOREST,
    TROPICAL_RAIN_FOREST,
    SUBTROPICAL_DESERT
};

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

    bool    haveNeighbor(Zone *zone);

    static int  indexMax;  // change this
    const int   index;

    Point       point;     // location
    bool        water;     // lake or ocean
    bool        ocean;     // ocean
    bool        coast;     // land polygon touching an ocean
    bool        border;    // at the edge of the map
    float       elevation; // 0.0-1.0
    float       moisture;  // 0.0-1.0

    MAP::Biome biome;     // biome type (see article)

    std::vector<Zone *>         neighbors;
    std::vector<CrossedEdge *>  borders;
    std::vector<Corner *>       corners;
};

}

#endif // ZONE_H
