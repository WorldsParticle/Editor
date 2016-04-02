#ifndef HEIGHTMAP_H
#define HEIGHTMAP_H

#include <vector>
#include <glm/glm.hpp>
#include "map/heightpoint.h"
#include "generator.h"
#include "zonelookup.h"
#include "tools/bitmap_image.h"

namespace MAP {

///
/// \brief The HeightMap class, propelling floor to space like a rocketeer
/// Based on the design found between two neurons
///
class HeightMap
{
public:
    HeightMap(int width, int height);
    ~HeightMap();

    void    init(MAP::Map & m);
    void    paintByMoisture();
    void    paintByHeight();
    void    paintByLandType();
    void    paintByBiome();

    void    generateMesh();

    std::vector<float> * getPoints();
    std::vector<int>     * getIndices();
    std::vector<float> * getNormals();

private:

    int _width;
    int _height;

    std::vector<HeightPoint>    _points;
    ZoneLookUp                  _zoneLookUp;
    bitmap_image                image;

    std::vector<float> * _vertices;
    std::vector<int>   * _indices;
    std::vector<float> * _normals;

};

}

#endif // HEIGHTMAP_H
