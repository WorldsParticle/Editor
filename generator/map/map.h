#ifndef MAP_H
#define MAP_H

#include <map>
#include "point.h"
#include "zone.h"
#include "corner.h"
#include "crossededge.h"
#include "zonelookup.h"

namespace MAP
{

class Map
{
public:
    Map(unsigned int xMax = 0, unsigned int yMax = 0, unsigned int zoneNumber = 0);
    ~Map();

    inline std::map<int, Zone *>        &zones()
    { return _zones; }
    inline std::map<int, Corner *>      &corners()
    { return _corners; }
    inline std::map<int, CrossedEdge *> &edges()
    { return _edges; }

    inline double xMax()
    { return _xMax; }
    inline double yMax()
    { return _yMax; }
    inline unsigned int zoneNumber()
    { return _zoneNumber; }

private:

    std::map<int, Zone *>         _zones;
    std::map<int, Corner *>       _corners;
    std::map<int, CrossedEdge *>  _edges;

    double    _xMax;
    double    _yMax;
    unsigned int    _zoneNumber;

    MAP::ZoneLookUp      _zoneLookUp;
};

}

#endif // MAP_H
