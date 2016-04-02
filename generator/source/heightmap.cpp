#include "include/heightmap.hpp"

#include <cstdlib>
#include <iostream>

#include "include/map/map.hpp"
#include "include/tools/simplexnoise.hpp"

namespace MAP
{


HeightMap::HeightMap(int width, int height) : _width(width), _height(height), _zoneLookUp(), image(width, height)
{
}

HeightMap::~HeightMap()
{
}

void    HeightMap::init(MAP::Map & m)
{
    int seed = rand() % 1000000;

    _points.resize((_width + 2) * (_height + 2));
    _zoneLookUp.createCloud(m);
    for (int i = 1; i <= _height; ++i)
    {
     for (int j = 1; j <= _width; ++j)
     {
         _points[i * _width + j].x = (double)j;
         _points[i * _width + j].y = (double)i;
         MAP::Zone * z;
         z = _zoneLookUp.getNearestZone((double)(j - 1), (double)(i - 1));
         _points[i * _width + j].zone = z;

         float  additionalNoise = octave_noise_2d(8, 0.5, 0.012, (float)j + seed, (float)i + seed);
         additionalNoise = additionalNoise / 10.0;


         _points[i * _width + j].z = (double)z->elevation; //+ additionalNoise;
         if (_points[i * _width + j].z > 1.0)
             _points[i * _width + j].z = 1.0;

     }
    }
}

void    HeightMap::paintByMoisture()
{
    for (int i = 1; i <= _height; ++i)
        for (int j = 1; j <= _width; ++j)
        {
            HeightPoint & p = _points[i * _width + j];
            if (p.zone->ocean)
                image.set_pixel(j - 1, _height - i, 0, 0, 125);
            else
                image.set_pixel(j - 1, _height - i, (int)(p.zone->moisture * 255.0), (int)(p.zone->moisture * 255.0), (int)(p.zone->moisture * 255.0));
        }
    image.save_image("mapmoisture.bmp");
}

void    HeightMap::paintByHeight()
{
    for (int i = 1; i <= _height; ++i)
        for (int j = 1; j <= _width; ++j)
        {
            HeightPoint & p = _points[i * _width + j];
            if (p.zone->ocean)
                image.set_pixel(j - 1, _height - i, 0, 0, 125);
            else
                image.set_pixel(j - 1, _height - i, (int)(p.z * 255.0), (int)(p.z * 255.0), (int)(p.z * 255.0));
        }
    image.save_image("mapheight.bmp");
}

void    HeightMap::paintByLandType()
{
    for (int i = 1; i <= _height; ++i)
        for (int j = 1; j <= _width; ++j)
        {
            HeightPoint & p = _points[i * _width + j];
            if (p.zone->border)
                image.set_pixel(j - 1, _height - i, 200, 50, 50);
            else if (p.zone->ocean)
                image.set_pixel(j - 1, _height - i, 50, 50, 200);
            else if (p.zone->coast)
                image.set_pixel(j - 1, _height - i, 255, 255, 204);
            else if (p.zone->water)
                image.set_pixel(j - 1, _height - i, 0, 255, 255);
        }
    image.save_image("maptype.bmp");
}

void    HeightMap::paintByBiome()
{
    for (int i = 1; i <= _height; ++i)
        for (int j = 1; j <= _width; ++j)
        {
            HeightPoint & p = _points[i * _width + j];
            if (p.zone->biome == MAP::BEACH)
                image.set_pixel(j - 1, _height - i, 255, 255, 204);
            else if (p.zone->biome == MAP::OCEAN)
                image.set_pixel(j - 1, _height - i, 26, 0, 153);
            else if (p.zone->biome == MAP::MARSH)
                image.set_pixel(j - 1, _height - i, 0, 204, 153);
            else if (p.zone->biome == MAP::ICE)
                image.set_pixel(j - 1, _height - i, 220, 250, 255);
            else if (p.zone->biome == MAP::LAKE)
                image.set_pixel(j - 1, _height - i, 61, 139, 255);
            else if (p.zone->biome == MAP::SNOW)
                image.set_pixel(j - 1, _height - i, 248, 248, 248);
            else if (p.zone->biome == MAP::TUNDRA)
                image.set_pixel(j - 1, _height - i, 208, 208, 176);
            else if (p.zone->biome == MAP::BARE)
                image.set_pixel(j - 1, _height - i, 176, 176, 176);
            else if (p.zone->biome == MAP::SCORCHED)
                image.set_pixel(j - 1, _height - i, 144, 144, 144);
            else if (p.zone->biome == MAP::TAIGA)
                image.set_pixel(j - 1, _height - i, 204, 212, 187);
            else if (p.zone->biome == MAP::SHRUBLAND)
                image.set_pixel(j - 1, _height - i, 196, 204, 187);
            else if (p.zone->biome == MAP::TEMPERATE_DESERT)
                image.set_pixel(j - 1, _height - i, 228, 232, 202);
            else if (p.zone->biome == MAP::TEMPERATE_RAIN_FOREST)
                image.set_pixel(j - 1, _height - i, 164, 196, 168);
            else if (p.zone->biome == MAP::TEMPERATE_DECIDUOUS_FOREST)
                image.set_pixel(j - 1, _height - i, 180, 196, 169);
            else if (p.zone->biome == MAP::GRASSLAND)
                image.set_pixel(j - 1, _height - i, 196, 212, 170);
            else if (p.zone->biome == MAP::TROPICAL_SEASONAL_FOREST)
                image.set_pixel(j - 1, _height - i, 169, 204, 164);
            else if (p.zone->biome == MAP::TROPICAL_RAIN_FOREST)
                image.set_pixel(j - 1, _height - i, 228, 232, 202);
            else if (p.zone->biome == MAP::SUBTROPICAL_DESERT)
                image.set_pixel(j - 1, _height - i, 233, 221, 199);

        }
    image.save_image("mapbiome.bmp");
}



void    HeightMap::generateMesh()
{
/*    _vertices = new std::vector<float>[_height * _width * 3];
    _indices = new std::vector<int>[(_height - 1) * (_width - 1) * 6];
    _normals = new std::vector<float>[(_height - 1) * (_width - 1) * 2 * 3];

    std::vector<float> & v = *_vertices;
    std::vector<int> &   i = *_indices;
    std::vector<float> & n = *_normals;

    for (int i = 1; i <= _height; ++i)
        for (int j = 1; j <= _width; ++j)
        {
            v[((i - 1) * _width + (j - 1)) * 3] = (float)(_points[i * _width + j].x);
            v[((i - 1) * _width + (j - 1)) * 3 + 1] = (float)(_points[i * _width + j].z);
            v[((i - 1) * _width + (j - 1)) * 3 + 2] = (float)(_points[i * _width + j].y);

            i[((i - 1) * _width + (j - 1)) * 6] = j + i * _width;
            i[((i - 1) * _width + (j - 1)) * 6 + 1] = j + 1 + (i + 1) * _width;
            i[((i - 1) * _width + (j - 1)) * 6 + 2] = j + (i + 1) * _width;

            i[((i - 1) * _width + (j - 1)) * 6 + 3] = j + i * _width;
            i[((i - 1) * _width + (j - 1)) * 6 + 4] = j + 1 + i * _width;
            i[((i - 1) * _width + (j - 1)) * 6 + 5] = j + 1 + (i + 1) * _width;

            glm::vec3 a;
            a = {_points[(i + 1) * _width + j].x - _points[i * _width + j].x,
                _points[(i + 1) * _width + j].z - _points[i * _width + j].z,
                _points[(i + 1) * _width + j].y - _points[i * _width + j].y};
            b = {_points[(i + 1) * _width + j + 1].x - _points[i * _width + j].x,
                _points[(i + 1) * _width + j + 1].z - _points[i * _width + j].z,
                _points[(i + 1) * _width + j + 1].y - _points[i * _width + j].y};
            c = {_points[i * _width + j].x - _points[i * _width + j].x,
                _points[i * _width + j].z - _points[i * _width + j].z,
                _points[i * _width + j].y - _points[i * _width + j].y};




        }*/
}

std::vector<float> * HeightMap::getPoints()     { return _vertices; }
std::vector<int>     * HeightMap::getIndices()   { return _indices; }
std::vector<float> * HeightMap::getNormals()     { return _normals; }

}
