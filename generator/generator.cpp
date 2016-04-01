#include "generator.h"

#include "map/map.h"
#include "voronoi/voronoi.h"
#include "shaper.h"
#include "elevator.h"
#include "riveror.h"
#include "moistor.h"
#include "biomizator.h"
#include "heightmap.h"

namespace GEN
{

Generator::Generator() :
    _map(NULL),
    _fillStep(NULL),
    _shapeStep(NULL),
    _elevateStep(NULL),
    _riverStep(NULL),
    _moistureStep(NULL),
    _biomeStep(NULL)
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

    _shapeStep = new SHA::Shaper();
    _shapeStep->generate(_map);

    _elevateStep = new ELE::Elevator();
    _elevateStep->generate(_map);

    _riverStep = new RIV::Riveror();
    _riverStep->generate(_map);

    MAP::HeightMap h(xMax, yMax);
    h.init(*_map);
    h.paint();

    _moistureStep = new MOI::Moistor();
    //_moistureStep->generate(_map);

    _biomeStep = new BIO::Biomizator();
    //_biomeStep->generate(_map);

    return _map;
}

}
