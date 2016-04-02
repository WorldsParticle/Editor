#include "include/generator.hpp"

#include "include/map/map.hpp"
#include "include/voronoi/voronoi.hpp"
#include "include/shaper.hpp"
#include "include/elevator.hpp"
#include "include/riveror.hpp"
#include "include/moistor.hpp"
#include "include/biomizator.hpp"
#include "include/heightmap.hpp"

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

    _moistureStep = new MOI::Moistor();
    _moistureStep->generate(_map);

    _biomeStep = new BIO::Biomizator();
    _biomeStep->generate(_map);

    MAP::HeightMap h(xMax, yMax);
    std::cout << "making heightmap..." << std::endl;
    h.init(*_map);
    std::cout << "painting..." << std::endl;
    h.paintByHeight();
    h.paintByMoisture();
    h.paintByLandType();
    h.paintByBiome();
std::cout << "painted..." << std::endl;

    return _map;
}

}
