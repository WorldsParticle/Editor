#include "map/map.h"

namespace MAP
{

Map::Map() :
    _zones(),
    _corners(),
    _edges()
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
