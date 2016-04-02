#include "biomizator.hpp"
#include <ctime>
#include <cstdlib>
#include <iostream>
#include <math.h>
#include <algorithm>

namespace BIO
{

Biomizator::Biomizator()
{
    _step = BIOMIZATING;
}

Biomizator::~Biomizator()
{
}

void    Biomizator::run()
{
    assignBiomes();
}


MAP::Biome        Biomizator::getBiome(MAP::Zone * z)
{
    if (z->ocean)
        return MAP::OCEAN;
    else if (z->water)
    {
        if (z->elevation < 0.1)
            return MAP::MARSH;
        if (z->elevation > 0.8)
            return MAP::ICE;
        return MAP::LAKE;
    }
    else if (z->coast)
        return MAP::BEACH;
    else if (z->elevation > 0.8)
    {
        if (z->moisture > 0.5)
            return MAP::SNOW;
        else if (z->moisture > 0.33)
            return MAP::TUNDRA;
        else if (z->moisture > 0.16)
            return MAP::BARE;
        else
            return MAP::SCORCHED;
    }
    else if (z->elevation > 0.6)
    {
        if (z->moisture > 0.66)
                return MAP::TAIGA;
        else if (z->moisture > 0.33)
                return MAP::SHRUBLAND;
        else
            return MAP::TEMPERATE_DESERT;
    }
    else if (z->elevation > 0.3)
    {
        if (z->moisture > 0.83)
            return MAP::TEMPERATE_RAIN_FOREST;
        else if (z->moisture > 0.50)
            return MAP::TEMPERATE_DECIDUOUS_FOREST;
        else if (z->moisture > 0.16)
            return MAP::GRASSLAND;
        else
            return MAP::TEMPERATE_DESERT;
    }
    else
    {
        if (z->moisture > 0.66)
            return MAP::TROPICAL_RAIN_FOREST;
        else if (z->moisture > 0.33)
            return MAP::TROPICAL_SEASONAL_FOREST;
        else if (z->moisture > 0.16)
            return MAP::GRASSLAND;
        else
            return (MAP::SUBTROPICAL_DESERT);
    }
}

void        Biomizator::assignBiomes()
{
    for (auto & z : _map->zones())
    {
        z.second->biome = getBiome(z.second);
    }
}

}
