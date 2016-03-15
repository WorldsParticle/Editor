#ifndef MAP_H
#define MAP_H

#include <map>
#include "point.h"
#include "zone.h"
#include "corner.h"
#include "crossededge.h"

namespace MAP
{

class Map
{
public:
    Map();
    ~Map();

    inline std::map<int, Zone *>        &zones()
    { return _zones; }
    inline std::map<int, Corner *>      &corners()
    { return _corners; }
    inline std::map<int, CrossedEdge *> &edges()
    { return _edges; }

private:

    std::map<int, Zone *>         _zones;
    std::map<int, Corner *>       _corners;
    std::map<int, CrossedEdge *>  _edges;

};

}

#endif // MAP_H
