#include "heightmap.h"

#include <ctime>
#include <cstdlib>
#include <iostream>
#include <math.h>
#include <algorithm>
#include <queue>

#include "map/map.h"
#include "tools/bitmap_image.h"

namespace MAP
{


HeightMap::HeightMap(int width, int height) : _width(width), _height(height), _zoneLookUp()
{
}

HeightMap::~HeightMap()
{
}

void    HeightMap::init(MAP::Map & m)
{
    _points.resize(_width * _height);
    _zoneLookUp.createCloud(m);
    for (int i = 0; i < _height; ++i)
    {
     for (int j = 0; j < _width; ++j)
     {
         _points[i * _width + j].x = (double)j;
         _points[i * _width + j].y = (double)i;
         MAP::Zone * z;
         z = _zoneLookUp.getNearestZone((double)j, (double)i);
         _points[i * _width + j].zone = z;
         _points[i * _width + j].z = (double)z->elevation;
     }
    }
}

void    HeightMap::paint()
{
    static bitmap_image image(_width, _height);

    for (int i = 0; i < _height; ++i)
        for (int j = 0; j < _width; ++j)
        {
            HeightPoint & p = _points[i * _width + j];
            if (p.zone->border)
                image.set_pixel(j, _height - i, 255, 0, 0);
            else if (p.zone->ocean)
                image.set_pixel(j, _height - i - 1, 0, 0, 125);
            else
            {
                image.set_pixel(j, _height - i - 1, (int)(p.z * 255.0), (int)(p.z * 255.0), (int)(p.z * 255.0));
            }
        }
    image.save_image("output.bmp");
}

}
