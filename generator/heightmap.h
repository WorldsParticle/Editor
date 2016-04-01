#ifndef HEIGHTMAP_H
#define HEIGHTMAP_H

#include "map/heightpoint.h"
#include "generator.h"
#include "zonelookup.h"

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
    void    paint();

private:

    int _width;
    int _height;

    std::vector<HeightPoint> _points;
    ZoneLookUp      _zoneLookUp;

};

}

#endif // HEIGHTMAP_H
