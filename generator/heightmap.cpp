#include "heightmap.h"

/*#include <ctime>
#include <cstdlib>
#include <iostream>
#include <math.h>
#include <algorithm>
#include <queue>*/

#include "map/map.h"

namespace MAP
{


HeightMap::HeightMap(int size) : _size(size)
{
    _points.resize(size * size);
}

HeightMap::~HeightMap()
{
}

void    HeightMap::assignHeight(const Map & m)
{

}

}
