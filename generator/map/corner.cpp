#include "map/corner.h"

namespace MAP
{

int Corner::indexMax = 0;
Corner::Corner() :
    index(indexMax),
    point(0, 0),
    faces(),
    edges(),
    adjacent()
{
    ++indexMax;
}

}
