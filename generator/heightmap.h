#ifndef HeightMap_H
#define HeightMap_H

#include "map/heightpoint.h"
#include "generator.h"

namespace MAP {

///
/// \brief The HeightMap class, propelling floor to space like a rocketeer
/// Based on the design found between two neurons
///
class HeightMap
{
public:
    HeightMap(int size);
    ~HeightMap();

    void    assignHeight(const MAP::Map & m);

private:

    int _size;

    std::vector<HeightPoint> _points;

};

}

#endif // HeightMap_H
