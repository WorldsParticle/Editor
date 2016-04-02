#include "elevator.hpp"
#include <ctime>
#include <cstdlib>
#include <iostream>
#include <math.h>
#include <algorithm>
#include <queue>

#include "map/map.hpp"

namespace ELE
{

Elevator::Elevator()
{
    _step = ELEVATE;
}

Elevator::~Elevator()
{
}

void    Elevator::run()
{
    assignCornerElevation();
    redistributeElevation();
    setPolygonElevation();
    calculateDownSlopes();
}


void        Elevator::assignCornerElevation()
{
    std::queue<MAP::Corner *>   q;
int a = 0;
    for (auto & corner : _map->corners())
    {

        if (corner.second->border)
        {
            ++a;
            corner.second->elevation = 0.0;
            q.push(corner.second);
        }
        else
            corner.second->elevation = std::numeric_limits<float>::max();
    }

    while (q.size())
    {
        auto * corner = q.front();
        q.pop();

        for (auto * adj : corner->adjacent)
        {
            float newElevation = 0.00001 + corner->elevation;
            if (!corner->water && !adj->water)
            {
                newElevation += 1;
                // add randomness here if map looks too dull
            }
            if (newElevation < adj->elevation)
            {
                adj->elevation = newElevation;
                q.push(adj);
            }
        }
    }
}


struct sortByElevation
{
  bool operator() (MAP::Corner const * L, MAP::Corner const * R) { return L->elevation < R->elevation; }
};

void        Elevator::redistributeElevation()
{
    float scaleFactor = 1.1;
    std::vector<MAP::Corner *> corners;

    for (const auto & corner : _map->corners())
    {
        if (!corner.second->ocean)
            corners.push_back(corner.second);
    }
    std::sort(corners.begin(), corners.end(), sortByElevation());

    for (unsigned int i = 0; i < corners.size(); ++i)
    {
       float y, x;

       y = (float)i / (float)(corners.size() - 1);
       x = sqrt(scaleFactor) - sqrt(scaleFactor * (1.0-y));
       if (x > 1.0)
           x = 1.0;
       corners[i]->elevation = x;
    }

}

void        Elevator::setPolygonElevation()
{
    for (const auto & zone : _map->zones())
    {
        float sumElevation = 0.0;
        for (auto * corner : zone.second->corners)
        {
            sumElevation += corner->elevation;
        }
        zone.second->elevation = sumElevation / zone.second->corners.size();
    }
}

void        Elevator::calculateDownSlopes()
{
    for (const auto & q : _map->corners())
    {
        auto * steepest = q.second;
        for (auto * neighbor : q.second->adjacent)
        {
            if (neighbor->elevation < steepest->elevation)
                steepest = neighbor;
        }
        q.second->downslope = steepest;
    }
}


}
