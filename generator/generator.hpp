#ifndef GENERATOR_H
#define GENERATOR_H

#include "generationstep.hpp"
#include <map>

namespace MAP
{
class Map;
}

namespace GEN
{

class Generator
{
public:
    Generator();

    MAP::Map    *generate(double xMax, double yMax, unsigned int zoneNumber);

protected:
    MAP::Map        *_map;
    GenerationStep  *_fillStep;
    GenerationStep  *_shapeStep;
    GenerationStep  *_elevateStep;
    GenerationStep  *_riverStep;
    GenerationStep  *_moistureStep;
    GenerationStep  *_biomeStep;
};

}

#endif // GENERATOR_H
