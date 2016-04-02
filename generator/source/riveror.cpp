#include "include/riveror.hpp"
#include <ctime>
#include <cstdlib>
#include <iostream>
#include <math.h>
#include <algorithm>

namespace RIV
{

Riveror::Riveror()
{
    _step = RIVERING;
}

Riveror::~Riveror()
{
}

void    Riveror::run()
{
    createRivers();
    calculateWatersheds();
}

void        Riveror::calculateWatersheds()
{
    for (auto & corner : _map->corners())
    {
        corner.second->watershed = corner.second;
        if (!corner.second->ocean && !corner.second->coast)
        {
            corner.second->watershed = corner.second->downslope;
        }
    }

    bool changed;
    for (int i = 0; i < 100; ++i)
    {
        changed = false;
        for (auto & c : _map->corners())
        {
            auto corner = c.second;
            if (!corner->ocean && !corner->coast && !corner->watershed->coast)
            {
                MAP::Corner * adj = corner->downslope->watershed;
                if (!adj->ocean)
                {
                    corner->watershed = adj;
                    changed = true;
                }
            }
        }
        if (!changed) break;
    }

    for (auto & corner : _map->corners())
    {
        MAP::Corner * adj = corner.second->watershed;
        adj->watershedSize += 1;
    }
}

void        Riveror::createRivers()
{
    for (unsigned int i; i < (_map->zoneNumber() / 2); ++i)
    {
        auto * corner = _map->corners().at(rand() % _map->corners().size());
        if (corner->ocean || corner->elevation < 0.3 || corner->elevation > 0.9)
            continue;
        while (!corner->coast)
        {
            if (corner->downslope == corner)
                break;
            MAP::CrossedEdge * edge = lookupEdgeFromCorner(corner, corner->downslope);
            edge->river += 1;
            corner->river += 1;
            corner->downslope->river += 1;
            corner = corner->downslope;
        }
    }
}

MAP::CrossedEdge * Riveror::lookupEdgeFromCorner(MAP::Corner * from, MAP::Corner * to)
{
    for (auto * edge : from->edges)
    {
        if (edge->c0 == to || edge->c1 == to)
            return (edge);
    }
    return (nullptr);
}


}
