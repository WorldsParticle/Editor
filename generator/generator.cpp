#include "generator.h"

#include "map/map.h"
#include "voronoi/voronoi.h"

namespace GEN
{

Generator::Generator() :
    _map(NULL),
    _fillStep(NULL),
    _shapeStep(NULL),
    _elevateStep(NULL)
{
    _fillStep = new VOR::Voronoi();
}

MAP::Map    *Generator::generate(double xMax, double yMax, unsigned int zoneNumber)
{
    _map = new MAP::Map(xMax, yMax, zoneNumber);

    MAP::Zone::indexMax = 0;
    MAP::Corner::indexMax = 0;
    MAP::CrossedEdge::indexMax = 0;

    _fillStep->generate(_map);

    return _map;
}

}
