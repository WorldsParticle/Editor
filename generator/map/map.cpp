#include "map/map.h"

namespace MAP
{

Map::Map(unsigned int xMax, unsigned int yMax, unsigned int zoneNumber) :
    _zones(),
    _corners(),
    _edges(),
    _xMax(xMax),
    _yMax(yMax),
    _zoneNumber(zoneNumber)
{

}

Map::~Map()
{
    for(std::map<int, Zone *>::iterator it = _zones.begin(); it != _zones.end(); ++it)
        delete (*it).second;
    for(std::map<int, Corner *>::iterator it = _corners.begin(); it != _corners.end(); ++it)
        delete (*it).second;
    for(std::map<int, CrossedEdge *>::iterator it = _edges.begin(); it != _edges.end(); ++it)
        delete (*it).second;

    _zones.clear();
    _corners.clear();
    _edges.clear();
}

}
