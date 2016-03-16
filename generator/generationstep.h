#ifndef GENERATIONSTEP_H
#define GENERATIONSTEP_H

#include "map/map.h"

namespace GEN
{

class GenerationStep
{
public:
    enum STEP
    {
        FILL = 0,
        SHAPE,
        ELEVATE,
        MOISTING,
        RIVERING,
        BIOMIZATING
    };

    GenerationStep() : _map(NULL) {}

    inline void    generate(MAP::Map *map)
    { _map = map; run(); }

protected:
    virtual void    run() = 0;
    MAP::Map        *_map;
    STEP            _step;
};

}

#endif // GENERATIONSTEP_H
