#include "generator.h"

#include "map/map.h"

namespace GEN
{

Generator::Generator() :
    _map(),
    _zoneNumber(0),
    _xMax(0),
    _yMax(0)
{

}

MAP::Map    *Generator::generate(double xMax, double yMax, unsigned int zoneNumber)
{
    _map = new MAP::Map();
    _xMax = xMax;
    _yMax = yMax;
    _zoneNumber = zoneNumber;

    MAP::Zone::indexMax = 0;
    MAP::Corner::indexMax = 0;
    MAP::CrossedEdge::indexMax = 0;

    run();
    return _map;
}

}
