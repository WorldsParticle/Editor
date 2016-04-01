#include <ctime>
#include <cstdlib>
#include <iostream>
#include <math.h>
#include <algorithm>
#include <queue>

#include "map/map.h"
#include "shaper.h"
#include "tools/simplexnoise.h"

namespace SHA
{

Shaper::Shaper()
{
    _step = SHAPE;
}

Shaper::~Shaper()
{
}

void    Shaper::run()
{
    assignCornerLandPerlin(rand() % 100000);
    assignOceanCostAndLand();
}

// TODO : assignCornerLandRadial()

void        Shaper::assignCornerLandPerlin(int seed)
{
    for (const auto & corner : _map->corners())
    {
        Point p = corner.second->point;
        double xMax = _map->xMax();
        double yMax = _map->yMax();

        // assign corner.border if a corner is out of the map's bounding box
        if (p.x <= 0 || p.y <= 0 || p.x >= xMax || p.y >= yMax)
            corner.second->border = true;
        else
            corner.second->border = false;

if (p.y > 500)
    std::cout << p.x << " " << p.y << std::endl;
        // put all corners inside for normalization, simplistic but doesn't affect outcome
        if (p.x > xMax)
            p.x = xMax;
        if (p.x < 0)
            p.x = 0;
        if (p.y > yMax)
            p.y = yMax;
        if (p.y < 0)
            p.y = 0;

        // perlin random number (z) € [0, 1], points are normalized to [-1, 1],
        // thus the farther a point from the center [0, 0],
        // the higher the threshold to earn the right to be a land corner as magnitude goes up.

        p.x = (p.x / xMax - 0.5) * 2;
        p.y = (p.y / yMax - 0.5) * 2;

        double magnitude = sqrt(pow(p.x, 2) + pow(p.y, 2));
        double z = (octave_noise_2d(8, 0.5, 0.3, p.x + seed, p.y + seed) + 1) / 2;
        double threshold = (0.3 + 0.3 * magnitude * magnitude);
        if (z > threshold && !corner.second->border)
            corner.second->water = false;
        else
            corner.second->water = true;
    }
}


void        Shaper::assignOceanCostAndLand()
{
    std::queue<MAP::Zone *> q;


    // assigning ocean to border zones,
    // and water based on corners
    for (auto & zone : _map->zones())
    {
        zone.second->ocean = false;
        int numWater = 0;
        for (auto * corner : zone.second->corners)
        {
            if (corner->border)
            {
               if (corner->point.y > 500)
                   std::cout << "->>" << corner->point.y << std::endl;
               zone.second->border = true;
               zone.second->ocean = true;
               corner->water = true;
               q.push(zone.second);
            }
            if (corner->water)
            {
                numWater += 1;
            }
        }
        zone.second->water = (zone.second->ocean || (numWater >= zone.second->corners.size() * 0.3)); // 0.3 == LAKE_TRESHOLD
    }

    // propagating ocean zones
    while (q.size())
    {
        auto * zone = q.front();
        q.pop();
        for (auto * neighbor : zone->neighbors)
        {
            if (neighbor->water && !neighbor->ocean) {
                neighbor->ocean = true;
                q.push(neighbor);
            }
        }
    }

    // assigning coast zones
    for (auto & zone : _map->zones())
    {
        int numOcean = 0;
        int numLand = 0;
        for (auto * neighbor : zone.second->neighbors)
        {
            numOcean += (int)(neighbor->ocean);
            numLand += (int)(!neighbor->water);
        }
        zone.second->coast = (numOcean > 0) && (numLand > 0);
    }

    // assigning corner's ocean, coast & water
    for (auto & corner : _map->corners())
    {
        unsigned int numOcean = 0;
        unsigned int numLand = 0;
        for (auto * zone : corner.second->faces)
        {
            numOcean += (int)(zone->ocean);
            numLand += (int)(!zone->water);
        }
        corner.second->ocean = (numOcean == corner.second->faces.size());
        corner.second->coast = (numOcean > 0) && (numLand > 0);
        corner.second->water = corner.second->border || ((numLand != corner.second->faces.size()) && !corner.second->coast);
    }
}


}
