#include "moistor.h"
#include <ctime>
#include <cstdlib>
#include <iostream>
#include <math.h>
#include <algorithm>
#include <queue>

#include "map/map.h"

namespace MOI
{

Moistor::Moistor()
{
    _step = MOISTING;
}

Moistor::~Moistor()
{
}

void    Moistor::run()
{
    assignCornerMoisture();
    assignPolygonMoisture();
}


void        Moistor::assignPolygonMoisture()
{
    for (auto & z : _map->zones())
    {
        float sumMoisture = 0.0;
        for (auto * corner : z.second->corners)
        {
            if (corner->moisture > 1.0)
                corner->moisture = 1.0;
            sumMoisture += corner->moisture;
        }
        z.second->moisture = sumMoisture / z.second->corners.size();
    }
}

void        Moistor::assignCornerMoisture()
{
    std::queue<MAP::Corner *> q;

    for (auto & c : _map->corners())
    {
        auto * corner = c.second;
        if ((corner->water || corner->river > 0) && !corner->ocean)
        {
            corner->moisture = corner->river > 0 ? std::min(3.0, (0.2 * corner->river)) : 1.0;
            q.push(corner);
        }
        else
        {
            corner->moisture = 0.0;
        }
    }

    float   newMoisture = 0.0;

    while (q.size())
    {
        auto * corner = q.front();
        q.pop();

        for (auto * adj : corner->adjacent)
        {
            newMoisture = corner->moisture * 0.9;
            if (newMoisture > adj->moisture)
            {
                adj->moisture = newMoisture;
                q.push(adj);
            }
        }
    }

    for (auto & corner : _map->corners())
    {
        if (corner.second->ocean || corner.second->coast)
            corner.second->moisture = 1.0;
    }
}


}
